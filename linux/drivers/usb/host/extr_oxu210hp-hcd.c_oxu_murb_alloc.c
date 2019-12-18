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
struct oxu_murb {int dummy; } ;
struct oxu_hcd {int* murb_used; int /*<<< orphan*/  mem_lock; struct oxu_murb* murb_pool; } ;

/* Variables and functions */
 int MURB_NUM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct oxu_murb *oxu_murb_alloc(struct oxu_hcd *oxu)

{
	int i;
	struct oxu_murb *murb = NULL;

	spin_lock(&oxu->mem_lock);

	for (i = 0; i < MURB_NUM; i++)
		if (!oxu->murb_used[i])
			break;

	if (i < MURB_NUM) {
		murb = &(oxu->murb_pool)[i];

		oxu->murb_used[i] = 1;
	}

	spin_unlock(&oxu->mem_lock);

	return murb;
}