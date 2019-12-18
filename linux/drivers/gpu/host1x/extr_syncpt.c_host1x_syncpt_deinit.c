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
struct host1x_syncpt {int /*<<< orphan*/  name; } ;
struct host1x {TYPE_1__* info; struct host1x_syncpt* syncpt; } ;
struct TYPE_2__ {unsigned int nb_pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void host1x_syncpt_deinit(struct host1x *host)
{
	struct host1x_syncpt *sp = host->syncpt;
	unsigned int i;

	for (i = 0; i < host->info->nb_pts; i++, sp++)
		kfree(sp->name);
}