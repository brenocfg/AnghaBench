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
struct host1x {TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int nb_bases; } ;

/* Variables and functions */

unsigned int host1x_syncpt_nb_bases(struct host1x *host)
{
	return host->info->nb_bases;
}