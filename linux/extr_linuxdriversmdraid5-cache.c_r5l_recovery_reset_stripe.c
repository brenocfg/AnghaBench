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
struct stripe_head {int disks; TYPE_1__* dev; int /*<<< orphan*/  log_start; scalar_t__ state; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MaxSector ; 

__attribute__((used)) static void r5l_recovery_reset_stripe(struct stripe_head *sh)
{
	int i;

	sh->state = 0;
	sh->log_start = MaxSector;
	for (i = sh->disks; i--; )
		sh->dev[i].flags = 0;
}