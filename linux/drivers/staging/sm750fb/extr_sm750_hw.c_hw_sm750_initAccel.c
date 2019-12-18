#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* de_init ) (TYPE_1__*) ;} ;
struct sm750_dev {TYPE_1__ accel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_STATE1 ; 
 int /*<<< orphan*/  DE_STATE1_DE_ABORT ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  SYSTEM_CTRL ; 
 int /*<<< orphan*/  SYSTEM_CTRL_DE_ABORT ; 
 int /*<<< orphan*/  peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_enable_2d_engine (int) ; 
 scalar_t__ sm750_get_chip_type () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void hw_sm750_initAccel(struct sm750_dev *sm750_dev)
{
	u32 reg;

	sm750_enable_2d_engine(1);

	if (sm750_get_chip_type() == SM750LE) {
		reg = peek32(DE_STATE1);
		reg |= DE_STATE1_DE_ABORT;
		poke32(DE_STATE1, reg);

		reg = peek32(DE_STATE1);
		reg &= ~DE_STATE1_DE_ABORT;
		poke32(DE_STATE1, reg);

	} else {
		/* engine reset */
		reg = peek32(SYSTEM_CTRL);
		reg |= SYSTEM_CTRL_DE_ABORT;
		poke32(SYSTEM_CTRL, reg);

		reg = peek32(SYSTEM_CTRL);
		reg &= ~SYSTEM_CTRL_DE_ABORT;
		poke32(SYSTEM_CTRL, reg);
	}

	/* call 2d init */
	sm750_dev->accel.de_init(&sm750_dev->accel);
}