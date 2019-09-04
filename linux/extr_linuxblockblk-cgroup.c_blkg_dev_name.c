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
struct blkcg_gq {TYPE_2__* q; } ;
struct TYPE_4__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_3__ {scalar_t__ dev; } ;

/* Variables and functions */
 char const* dev_name (scalar_t__) ; 

const char *blkg_dev_name(struct blkcg_gq *blkg)
{
	/* some drivers (floppy) instantiate a queue w/o disk registered */
	if (blkg->q->backing_dev_info->dev)
		return dev_name(blkg->q->backing_dev_info->dev);
	return NULL;
}