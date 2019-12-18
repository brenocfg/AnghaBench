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
struct ivtv {TYPE_1__* api_cache; } ;
struct TYPE_2__ {scalar_t__ last_jiffies; } ;

/* Variables and functions */

void ivtv_mailbox_cache_invalidate(struct ivtv *itv)
{
	int i;
	for (i = 0; i < 256; i++)
		itv->api_cache[i].last_jiffies = 0;
}