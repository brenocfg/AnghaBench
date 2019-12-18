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
struct ispif_device {int /*<<< orphan*/  clock_for_reset; int /*<<< orphan*/  nclocks_for_reset; int /*<<< orphan*/  reset_complete; scalar_t__ base; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ISPIF_RESET_TIMEOUT_MS ; 
 scalar_t__ ISPIF_RST_CMD_0 ; 
 int ISPIF_RST_CMD_0_MISC_LOGIC_RST ; 
 int ISPIF_RST_CMD_0_PIX_INTF_0_CSID_RST ; 
 int ISPIF_RST_CMD_0_PIX_INTF_0_VFE_RST ; 
 int ISPIF_RST_CMD_0_PIX_INTF_1_CSID_RST ; 
 int ISPIF_RST_CMD_0_PIX_INTF_1_VFE_RST ; 
 int ISPIF_RST_CMD_0_PIX_OUTPUT_0_MISR_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_0_CSID_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_0_VFE_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_1_CSID_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_1_VFE_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_2_CSID_RST ; 
 int ISPIF_RST_CMD_0_RDI_INTF_2_VFE_RST ; 
 int ISPIF_RST_CMD_0_RDI_OUTPUT_0_MISR_RST ; 
 int ISPIF_RST_CMD_0_RDI_OUTPUT_1_MISR_RST ; 
 int ISPIF_RST_CMD_0_RDI_OUTPUT_2_MISR_RST ; 
 int ISPIF_RST_CMD_0_STROBED_RST_EN ; 
 int ISPIF_RST_CMD_0_SW_REG_RST ; 
 int /*<<< orphan*/  PM_DOMAIN_VFE0 ; 
 int /*<<< orphan*/  PM_DOMAIN_VFE1 ; 
 int /*<<< orphan*/  camss_disable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camss_enable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camss_pm_domain_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camss_pm_domain_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_camss (struct ispif_device*) ; 
 int /*<<< orphan*/  to_device (struct ispif_device*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int ispif_reset(struct ispif_device *ispif)
{
	unsigned long time;
	u32 val;
	int ret;

	ret = camss_pm_domain_on(to_camss(ispif), PM_DOMAIN_VFE0);
	if (ret < 0)
		return ret;

	ret = camss_pm_domain_on(to_camss(ispif), PM_DOMAIN_VFE1);
	if (ret < 0)
		return ret;

	ret = camss_enable_clocks(ispif->nclocks_for_reset,
				  ispif->clock_for_reset,
				  to_device(ispif));
	if (ret < 0)
		return ret;

	reinit_completion(&ispif->reset_complete);

	val = ISPIF_RST_CMD_0_STROBED_RST_EN |
		ISPIF_RST_CMD_0_MISC_LOGIC_RST |
		ISPIF_RST_CMD_0_SW_REG_RST |
		ISPIF_RST_CMD_0_PIX_INTF_0_CSID_RST |
		ISPIF_RST_CMD_0_PIX_INTF_0_VFE_RST |
		ISPIF_RST_CMD_0_PIX_INTF_1_CSID_RST |
		ISPIF_RST_CMD_0_PIX_INTF_1_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_0_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_0_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_1_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_1_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_2_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_2_VFE_RST |
		ISPIF_RST_CMD_0_PIX_OUTPUT_0_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_0_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_1_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_2_MISR_RST;

	writel_relaxed(val, ispif->base + ISPIF_RST_CMD_0);

	time = wait_for_completion_timeout(&ispif->reset_complete,
		msecs_to_jiffies(ISPIF_RESET_TIMEOUT_MS));
	if (!time) {
		dev_err(to_device(ispif), "ISPIF reset timeout\n");
		ret = -EIO;
	}

	camss_disable_clocks(ispif->nclocks_for_reset, ispif->clock_for_reset);

	camss_pm_domain_off(to_camss(ispif), PM_DOMAIN_VFE0);
	camss_pm_domain_off(to_camss(ispif), PM_DOMAIN_VFE1);

	return ret;
}