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
struct area_priv {int flags; } ;
struct anybuss_host {int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  power_on; } ;
struct ab_task {scalar_t__ start_jiffies; struct area_priv area_pd; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ TIMEOUT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int task_fn_area_3(struct anybuss_host *cd, struct ab_task *t)
{
	struct area_priv *pd = &t->area_pd;

	if (!cd->power_on)
		return -EIO;
	if (atomic_read(&cd->ind_ab) & pd->flags) {
		/* area not released yet */
		if (time_after(jiffies, t->start_jiffies + TIMEOUT))
			return -ETIMEDOUT;
		return -EINPROGRESS;
	}
	return 0;
}