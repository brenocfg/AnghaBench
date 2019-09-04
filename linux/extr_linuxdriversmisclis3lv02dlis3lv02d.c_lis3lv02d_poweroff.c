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
struct lis3lv02d {int /*<<< orphan*/  (* reg_ctrl ) (struct lis3lv02d*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct lis3lv02d*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG1 ; 
 int /*<<< orphan*/  LIS3_REG_OFF ; 
 int /*<<< orphan*/  lis3_context_save (struct lis3lv02d*) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 

void lis3lv02d_poweroff(struct lis3lv02d *lis3)
{
	if (lis3->reg_ctrl)
		lis3_context_save(lis3);
	/* disable X,Y,Z axis and power down */
	lis3->write(lis3, CTRL_REG1, 0x00);
	if (lis3->reg_ctrl)
		lis3->reg_ctrl(lis3, LIS3_REG_OFF);
}