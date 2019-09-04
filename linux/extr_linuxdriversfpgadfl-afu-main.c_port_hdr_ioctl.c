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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dfl_feature {int dummy; } ;

/* Variables and functions */
#define  DFL_FPGA_PORT_RESET 128 
 long EINVAL ; 
 long ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 long port_reset (struct platform_device*) ; 

__attribute__((used)) static long
port_hdr_ioctl(struct platform_device *pdev, struct dfl_feature *feature,
	       unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd) {
	case DFL_FPGA_PORT_RESET:
		if (!arg)
			ret = port_reset(pdev);
		else
			ret = -EINVAL;
		break;
	default:
		dev_dbg(&pdev->dev, "%x cmd not handled", cmd);
		ret = -ENODEV;
	}

	return ret;
}