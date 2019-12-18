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
struct cpwd {TYPE_1__* devs; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WD_BLIMIT ; 
 int /*<<< orphan*/  WD_INTR_ON ; 
 scalar_t__ WD_LIMIT ; 
 int /*<<< orphan*/  cpwd_toggleintr (struct cpwd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpwd_writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cpwd_resetbrokentimer(struct cpwd *p, int index)
{
	cpwd_toggleintr(p, index, WD_INTR_ON);
	cpwd_writew(WD_BLIMIT, p->devs[index].regs + WD_LIMIT);
}