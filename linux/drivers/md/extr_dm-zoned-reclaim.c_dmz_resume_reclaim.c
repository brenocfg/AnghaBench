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
struct dmz_reclaim {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_IDLE_PERIOD ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dmz_resume_reclaim(struct dmz_reclaim *zrc)
{
	queue_delayed_work(zrc->wq, &zrc->work, DMZ_IDLE_PERIOD);
}