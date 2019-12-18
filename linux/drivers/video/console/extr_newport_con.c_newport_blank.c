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
struct vc_data {int dummy; } ;

/* Variables and functions */
 unsigned short VC2_CTRL_EDISP ; 
 int /*<<< orphan*/  VC2_IREG_CONTROL ; 
 unsigned short newport_vc2_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newport_vc2_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  npregs ; 

__attribute__((used)) static int newport_blank(struct vc_data *c, int blank, int mode_switch)
{
	unsigned short treg;

	if (blank == 0) {
		/* unblank console */
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg | VC2_CTRL_EDISP));
	} else {
		/* blank console */
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg & ~(VC2_CTRL_EDISP)));
	}
	return 1;
}