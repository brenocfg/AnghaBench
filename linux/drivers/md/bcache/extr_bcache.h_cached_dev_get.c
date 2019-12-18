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
struct cached_dev {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static inline bool cached_dev_get(struct cached_dev *dc)
{
	if (!refcount_inc_not_zero(&dc->count))
		return false;

	/* Paired with the mb in cached_dev_attach */
	smp_mb__after_atomic();
	return true;
}