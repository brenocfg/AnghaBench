#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clcd_regs {int /*<<< orphan*/  cntl; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {TYPE_1__ green; } ;
struct TYPE_6__ {TYPE_2__ var; } ;
struct clcd_fb {TYPE_3__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTL_BGR ; 
 int /*<<< orphan*/  clcdfb_decode (struct clcd_fb*,struct clcd_regs*) ; 

__attribute__((used)) static void versatile_clcd_decode(struct clcd_fb *fb, struct clcd_regs *regs)
{
	clcdfb_decode(fb, regs);

	/* Always clear BGR for RGB565: we do the routing externally */
	if (fb->fb.var.green.length == 6)
		regs->cntl &= ~CNTL_BGR;
}