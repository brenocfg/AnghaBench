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
struct qib_pportdata {TYPE_1__* cpspec; TYPE_3__* dd; } ;
struct TYPE_6__ {TYPE_2__* cspec; } ;
struct TYPE_5__ {int /*<<< orphan*/  r1; } ;
struct TYPE_4__ {int /*<<< orphan*/  h1_val; scalar_t__ qdr_reforce; } ;

/* Variables and functions */
 int SERDES_CHANS ; 
 int /*<<< orphan*/  clock_man (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  set_man_code (struct qib_pportdata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_man_mode_h1 (struct qib_pportdata*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void force_h1(struct qib_pportdata *ppd)
{
	int chan;

	ppd->cpspec->qdr_reforce = 0;
	if (!ppd->dd->cspec->r1)
		return;

	for (chan = 0; chan < SERDES_CHANS; chan++) {
		set_man_mode_h1(ppd, chan, 1, 0);
		set_man_code(ppd, chan, ppd->cpspec->h1_val);
		clock_man(ppd, chan);
		set_man_mode_h1(ppd, chan, 0, 0);
	}
}