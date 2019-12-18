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
struct lis3lv02d {scalar_t__ whoami; scalar_t__ reg_ctrl; int /*<<< orphan*/  (* write ) (struct lis3lv02d*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ;scalar_t__ pdata; int /*<<< orphan*/  (* init ) (struct lis3lv02d*) ;} ;

/* Variables and functions */
 int CTRL2_BDU ; 
 int CTRL2_BOOT ; 
 int CTRL2_BOOT_3DLH ; 
 int CTRL2_BOOT_8B ; 
 int CTRL4_BDU ; 
 int /*<<< orphan*/  CTRL_REG2 ; 
 int /*<<< orphan*/  CTRL_REG4 ; 
 scalar_t__ WAI_12B ; 
 scalar_t__ WAI_3DLH ; 
 int /*<<< orphan*/  lis3_context_restore (struct lis3lv02d*) ; 
 int lis3lv02d_get_pwron_wait (struct lis3lv02d*) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct lis3lv02d*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct lis3lv02d*,int /*<<< orphan*/ ,int) ; 

int lis3lv02d_poweron(struct lis3lv02d *lis3)
{
	int err;
	u8 reg;

	lis3->init(lis3);

	/*
	 * Common configuration
	 * BDU: (12 bits sensors only) LSB and MSB values are not updated until
	 *      both have been read. So the value read will always be correct.
	 * Set BOOT bit to refresh factory tuning values.
	 */
	if (lis3->pdata) {
		lis3->read(lis3, CTRL_REG2, &reg);
		if (lis3->whoami ==  WAI_12B)
			reg |= CTRL2_BDU | CTRL2_BOOT;
		else if (lis3->whoami ==  WAI_3DLH)
			reg |= CTRL2_BOOT_3DLH;
		else
			reg |= CTRL2_BOOT_8B;
		lis3->write(lis3, CTRL_REG2, reg);

		if (lis3->whoami ==  WAI_3DLH) {
			lis3->read(lis3, CTRL_REG4, &reg);
			reg |= CTRL4_BDU;
			lis3->write(lis3, CTRL_REG4, reg);
		}
	}

	err = lis3lv02d_get_pwron_wait(lis3);
	if (err)
		return err;

	if (lis3->reg_ctrl)
		lis3_context_restore(lis3);

	return 0;
}