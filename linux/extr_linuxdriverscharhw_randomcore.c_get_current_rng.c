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
struct hwrng {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 struct hwrng* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct hwrng* current_rng ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rng_mutex ; 

__attribute__((used)) static struct hwrng *get_current_rng(void)
{
	struct hwrng *rng;

	if (mutex_lock_interruptible(&rng_mutex))
		return ERR_PTR(-ERESTARTSYS);

	rng = current_rng;
	if (rng)
		kref_get(&rng->ref);

	mutex_unlock(&rng_mutex);
	return rng;
}