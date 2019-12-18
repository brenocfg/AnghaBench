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
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ all_bits_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int ufx_reg_read (struct ufx_data*,int,int /*<<< orphan*/ *) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_config_ddr2(struct ufx_data *dev)
{
	int status, i = 0;
	u32 tmp;

	status = ufx_reg_write(dev, 0x0004, 0x001F0F77);
	check_warn_return(status, "error writing 0x0004");

	status = ufx_reg_write(dev, 0x0008, 0xFFF00000);
	check_warn_return(status, "error writing 0x0008");

	status = ufx_reg_write(dev, 0x000C, 0x0FFF2222);
	check_warn_return(status, "error writing 0x000C");

	status = ufx_reg_write(dev, 0x0010, 0x00030814);
	check_warn_return(status, "error writing 0x0010");

	status = ufx_reg_write(dev, 0x0014, 0x00500019);
	check_warn_return(status, "error writing 0x0014");

	status = ufx_reg_write(dev, 0x0018, 0x020D0F15);
	check_warn_return(status, "error writing 0x0018");

	status = ufx_reg_write(dev, 0x001C, 0x02532305);
	check_warn_return(status, "error writing 0x001C");

	status = ufx_reg_write(dev, 0x0020, 0x0B030905);
	check_warn_return(status, "error writing 0x0020");

	status = ufx_reg_write(dev, 0x0024, 0x00000827);
	check_warn_return(status, "error writing 0x0024");

	status = ufx_reg_write(dev, 0x0028, 0x00000000);
	check_warn_return(status, "error writing 0x0028");

	status = ufx_reg_write(dev, 0x002C, 0x00000042);
	check_warn_return(status, "error writing 0x002C");

	status = ufx_reg_write(dev, 0x0030, 0x09520000);
	check_warn_return(status, "error writing 0x0030");

	status = ufx_reg_write(dev, 0x0034, 0x02223314);
	check_warn_return(status, "error writing 0x0034");

	status = ufx_reg_write(dev, 0x0038, 0x00430043);
	check_warn_return(status, "error writing 0x0038");

	status = ufx_reg_write(dev, 0x003C, 0xF00F000F);
	check_warn_return(status, "error writing 0x003C");

	status = ufx_reg_write(dev, 0x0040, 0xF380F00F);
	check_warn_return(status, "error writing 0x0040");

	status = ufx_reg_write(dev, 0x0044, 0xF00F0496);
	check_warn_return(status, "error writing 0x0044");

	status = ufx_reg_write(dev, 0x0048, 0x03080406);
	check_warn_return(status, "error writing 0x0048");

	status = ufx_reg_write(dev, 0x004C, 0x00001000);
	check_warn_return(status, "error writing 0x004C");

	status = ufx_reg_write(dev, 0x005C, 0x00000007);
	check_warn_return(status, "error writing 0x005C");

	status = ufx_reg_write(dev, 0x0100, 0x54F00012);
	check_warn_return(status, "error writing 0x0100");

	status = ufx_reg_write(dev, 0x0104, 0x00004012);
	check_warn_return(status, "error writing 0x0104");

	status = ufx_reg_write(dev, 0x0118, 0x40404040);
	check_warn_return(status, "error writing 0x0118");

	status = ufx_reg_write(dev, 0x0000, 0x00000001);
	check_warn_return(status, "error writing 0x0000");

	while (i++ < 500) {
		status = ufx_reg_read(dev, 0x0000, &tmp);
		check_warn_return(status, "error reading 0x0000");

		if (all_bits_set(tmp, 0xC0000000))
			return 0;
	}

	pr_err("DDR2 initialisation timed out, reg 0x0000=0x%08x", tmp);
	return -ETIMEDOUT;
}