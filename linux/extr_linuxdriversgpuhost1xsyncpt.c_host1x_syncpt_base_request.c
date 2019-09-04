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
struct host1x_syncpt_base {int requested; } ;
struct host1x {TYPE_1__* info; struct host1x_syncpt_base* bases; } ;
struct TYPE_2__ {unsigned int nb_bases; } ;

/* Variables and functions */

__attribute__((used)) static struct host1x_syncpt_base *
host1x_syncpt_base_request(struct host1x *host)
{
	struct host1x_syncpt_base *bases = host->bases;
	unsigned int i;

	for (i = 0; i < host->info->nb_bases; i++)
		if (!bases[i].requested)
			break;

	if (i >= host->info->nb_bases)
		return NULL;

	bases[i].requested = true;
	return &bases[i];
}