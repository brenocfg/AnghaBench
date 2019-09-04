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
struct srp_fr_pool {int size; struct srp_fr_desc* desc; } ;
struct srp_fr_desc {scalar_t__ mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dereg_mr (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct srp_fr_pool*) ; 

__attribute__((used)) static void srp_destroy_fr_pool(struct srp_fr_pool *pool)
{
	int i;
	struct srp_fr_desc *d;

	if (!pool)
		return;

	for (i = 0, d = &pool->desc[0]; i < pool->size; i++, d++) {
		if (d->mr)
			ib_dereg_mr(d->mr);
	}
	kfree(pool);
}