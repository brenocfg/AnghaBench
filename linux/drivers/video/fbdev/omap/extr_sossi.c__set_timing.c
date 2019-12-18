#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int fck_hz; int /*<<< orphan*/  fck; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOSSI_INIT1_REG ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_2__ sossi ; 
 int sossi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sossi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _set_timing(int div, int tw0, int tw1)
{
	u32 l;

#ifdef VERBOSE
	dev_dbg(sossi.fbdev->dev, "Using TW0 = %d, TW1 = %d, div = %d\n",
		 tw0 + 1, tw1 + 1, div);
#endif

	clk_set_rate(sossi.fck, sossi.fck_hz / div);
	clk_enable(sossi.fck);
	l = sossi_read_reg(SOSSI_INIT1_REG);
	l &= ~((0x0f << 20) | (0x3f << 24));
	l |= (tw0 << 20) | (tw1 << 24);
	sossi_write_reg(SOSSI_INIT1_REG, l);
	clk_disable(sossi.fck);
}