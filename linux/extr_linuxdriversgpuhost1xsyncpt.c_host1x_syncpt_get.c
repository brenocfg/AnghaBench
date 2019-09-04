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
struct host1x_syncpt {int dummy; } ;
struct host1x {struct host1x_syncpt* syncpt; TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int nb_pts; } ;

/* Variables and functions */

struct host1x_syncpt *host1x_syncpt_get(struct host1x *host, unsigned int id)
{
	if (id >= host->info->nb_pts)
		return NULL;

	return host->syncpt + id;
}