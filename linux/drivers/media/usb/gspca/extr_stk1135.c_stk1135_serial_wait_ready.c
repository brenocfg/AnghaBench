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
typedef  int u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1135_REG_SICTL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reg_r (struct gspca_dev*,scalar_t__) ; 

__attribute__((used)) static int stk1135_serial_wait_ready(struct gspca_dev *gspca_dev)
{
	int i = 0;
	u8 val;

	do {
		val = reg_r(gspca_dev, STK1135_REG_SICTL + 1);
		if (i++ > 500) { /* maximum retry count */
			pr_err("serial bus timeout: status=0x%02x\n", val);
			return -1;
		}
	/* repeat if BUSY or WRITE/READ not finished */
	} while ((val & 0x10) || !(val & 0x05));

	return 0;
}