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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mem; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMF_ON ; 
 TYPE_1__ cmb_area ; 
 int /*<<< orphan*/  cmf_activate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cmf_reactivate(void)
{
	spin_lock(&cmb_area.lock);
	if (!list_empty(&cmb_area.list))
		cmf_activate(cmb_area.mem, CMF_ON);
	spin_unlock(&cmb_area.lock);
}