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
typedef  int /*<<< orphan*/  u32 ;
struct vme_lm_resource {int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct fake_driver {unsigned long long lm_base; int lm_enabled; int /*<<< orphan*/  lm_cycle; int /*<<< orphan*/  lm_aspace; } ;
struct TYPE_2__ {struct fake_driver* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fake_lm_get(struct vme_lm_resource *lm,
		unsigned long long *lm_base, u32 *aspace, u32 *cycle)
{
	struct fake_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	*lm_base = bridge->lm_base;
	*aspace = bridge->lm_aspace;
	*cycle = bridge->lm_cycle;

	mutex_unlock(&lm->mtx);

	return bridge->lm_enabled;
}