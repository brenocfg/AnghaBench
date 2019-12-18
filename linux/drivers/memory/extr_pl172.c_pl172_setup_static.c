#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct pl172_data {scalar_t__ base; } ;
struct device_node {int dummy; } ;
struct amba_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MPMC_STATIC_CFG (int) ; 
 int MPMC_STATIC_CFG_B ; 
 int MPMC_STATIC_CFG_EW ; 
 int MPMC_STATIC_CFG_MW_16BIT ; 
 int MPMC_STATIC_CFG_MW_32BIT ; 
 int MPMC_STATIC_CFG_MW_8BIT ; 
 int MPMC_STATIC_CFG_P ; 
 int MPMC_STATIC_CFG_PB ; 
 int MPMC_STATIC_CFG_PC ; 
 int MPMC_STATIC_CFG_PM ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_OEN (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_OEN_MAX ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_PAGE (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_PAGE_MAX ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_RD (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_RD_MAX ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_TURN (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_TURN_MAX ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_WEN (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_WEN_MAX ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_WR (int) ; 
 int /*<<< orphan*/  MPMC_STATIC_WAIT_WR_MAX ; 
 struct pl172_data* amba_get_drvdata (struct amba_device*) ; 
 int amba_part (struct amba_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int pl172_timing_prop (struct amba_device*,struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pl172_setup_static(struct amba_device *adev,
			      struct device_node *np, u32 cs)
{
	struct pl172_data *pl172 = amba_get_drvdata(adev);
	u32 cfg;
	int ret;

	/* MPMC static memory configuration */
	if (!of_property_read_u32(np, "mpmc,memory-width", &cfg)) {
		if (cfg == 8) {
			cfg = MPMC_STATIC_CFG_MW_8BIT;
		} else if (cfg == 16) {
			cfg = MPMC_STATIC_CFG_MW_16BIT;
		} else if (cfg == 32) {
			cfg = MPMC_STATIC_CFG_MW_32BIT;
		} else {
			dev_err(&adev->dev, "invalid memory width cs%u\n", cs);
			return -EINVAL;
		}
	} else {
		dev_err(&adev->dev, "memory-width property required\n");
		return -EINVAL;
	}

	if (of_property_read_bool(np, "mpmc,async-page-mode"))
		cfg |= MPMC_STATIC_CFG_PM;

	if (of_property_read_bool(np, "mpmc,cs-active-high"))
		cfg |= MPMC_STATIC_CFG_PC;

	if (of_property_read_bool(np, "mpmc,byte-lane-low"))
		cfg |= MPMC_STATIC_CFG_PB;

	if (of_property_read_bool(np, "mpmc,extended-wait"))
		cfg |= MPMC_STATIC_CFG_EW;

	if (amba_part(adev) == 0x172 &&
	    of_property_read_bool(np, "mpmc,buffer-enable"))
		cfg |= MPMC_STATIC_CFG_B;

	if (of_property_read_bool(np, "mpmc,write-protect"))
		cfg |= MPMC_STATIC_CFG_P;

	writel(cfg, pl172->base + MPMC_STATIC_CFG(cs));
	dev_dbg(&adev->dev, "mpmc static config cs%u: 0x%08x\n", cs, cfg);

	/* MPMC static memory timing */
	ret = pl172_timing_prop(adev, np, "mpmc,write-enable-delay",
				MPMC_STATIC_WAIT_WEN(cs),
				MPMC_STATIC_WAIT_WEN_MAX, 1);
	if (ret)
		goto fail;

	ret = pl172_timing_prop(adev, np, "mpmc,output-enable-delay",
				MPMC_STATIC_WAIT_OEN(cs),
				MPMC_STATIC_WAIT_OEN_MAX, 0);
	if (ret)
		goto fail;

	ret = pl172_timing_prop(adev, np, "mpmc,read-access-delay",
				MPMC_STATIC_WAIT_RD(cs),
				MPMC_STATIC_WAIT_RD_MAX, 1);
	if (ret)
		goto fail;

	ret = pl172_timing_prop(adev, np, "mpmc,page-mode-read-delay",
				MPMC_STATIC_WAIT_PAGE(cs),
				MPMC_STATIC_WAIT_PAGE_MAX, 1);
	if (ret)
		goto fail;

	ret = pl172_timing_prop(adev, np, "mpmc,write-access-delay",
				MPMC_STATIC_WAIT_WR(cs),
				MPMC_STATIC_WAIT_WR_MAX, 2);
	if (ret)
		goto fail;

	ret = pl172_timing_prop(adev, np, "mpmc,turn-round-delay",
				MPMC_STATIC_WAIT_TURN(cs),
				MPMC_STATIC_WAIT_TURN_MAX, 1);
	if (ret)
		goto fail;

	return 0;
fail:
	dev_err(&adev->dev, "failed to configure cs%u\n", cs);
	return ret;
}