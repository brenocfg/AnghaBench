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
struct dsaf_device {int /*<<< orphan*/  sc_base; scalar_t__ sub_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsaf_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_syscon (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsaf_write_sub(struct dsaf_device *dsaf_dev, u32 reg, u32 val)
{
	if (dsaf_dev->sub_ctrl)
		dsaf_write_syscon(dsaf_dev->sub_ctrl, reg, val);
	else
		dsaf_write_reg(dsaf_dev->sc_base, reg, val);
}