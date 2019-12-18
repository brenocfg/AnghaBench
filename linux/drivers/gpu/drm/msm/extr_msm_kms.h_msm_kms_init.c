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
struct msm_kms_funcs {int dummy; } ;
struct msm_kms {int /*<<< orphan*/ * pending_timers; struct msm_kms_funcs const* funcs; int /*<<< orphan*/  commit_lock; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_atomic_init_pending_timer (int /*<<< orphan*/ *,struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void msm_kms_init(struct msm_kms *kms,
		const struct msm_kms_funcs *funcs)
{
	unsigned i;

	mutex_init(&kms->commit_lock);
	kms->funcs = funcs;

	for (i = 0; i < ARRAY_SIZE(kms->pending_timers); i++)
		msm_atomic_init_pending_timer(&kms->pending_timers[i], kms, i);
}