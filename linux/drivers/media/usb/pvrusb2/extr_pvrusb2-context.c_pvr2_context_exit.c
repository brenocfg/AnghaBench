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
struct pvr2_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  disconnect_flag; scalar_t__ mc_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_context_notify (struct pvr2_context*) ; 

__attribute__((used)) static void pvr2_context_exit(struct pvr2_context *mp)
{
	int destroy_flag = 0;
	if (!(mp->mc_first || !mp->disconnect_flag)) {
		destroy_flag = !0;
	}
	mutex_unlock(&mp->mutex);
	if (destroy_flag) pvr2_context_notify(mp);
}