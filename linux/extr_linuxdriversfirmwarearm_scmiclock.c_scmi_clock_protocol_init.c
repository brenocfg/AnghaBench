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
typedef  int /*<<< orphan*/  u32 ;
struct scmi_handle {struct clock_info* clk_priv; int /*<<< orphan*/ * clk_ops; int /*<<< orphan*/  dev; } ;
struct scmi_clock_info {int dummy; } ;
struct clock_info {int num_clocks; struct scmi_clock_info* clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PROTOCOL_REV_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOL_REV_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_CLOCK ; 
 int /*<<< orphan*/  clk_ops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scmi_clock_info* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct clock_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int scmi_clock_attributes_get (struct scmi_handle*,int,struct scmi_clock_info*) ; 
 int /*<<< orphan*/  scmi_clock_describe_rates_get (struct scmi_handle*,int,struct scmi_clock_info*) ; 
 int /*<<< orphan*/  scmi_clock_protocol_attributes_get (struct scmi_handle*,struct clock_info*) ; 
 int /*<<< orphan*/  scmi_version_get (struct scmi_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scmi_clock_protocol_init(struct scmi_handle *handle)
{
	u32 version;
	int clkid, ret;
	struct clock_info *cinfo;

	scmi_version_get(handle, SCMI_PROTOCOL_CLOCK, &version);

	dev_dbg(handle->dev, "Clock Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	cinfo = devm_kzalloc(handle->dev, sizeof(*cinfo), GFP_KERNEL);
	if (!cinfo)
		return -ENOMEM;

	scmi_clock_protocol_attributes_get(handle, cinfo);

	cinfo->clk = devm_kcalloc(handle->dev, cinfo->num_clocks,
				  sizeof(*cinfo->clk), GFP_KERNEL);
	if (!cinfo->clk)
		return -ENOMEM;

	for (clkid = 0; clkid < cinfo->num_clocks; clkid++) {
		struct scmi_clock_info *clk = cinfo->clk + clkid;

		ret = scmi_clock_attributes_get(handle, clkid, clk);
		if (!ret)
			scmi_clock_describe_rates_get(handle, clkid, clk);
	}

	handle->clk_ops = &clk_ops;
	handle->clk_priv = cinfo;

	return 0;
}