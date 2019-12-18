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
struct oxu_hcd {int /*<<< orphan*/  mem_lock; scalar_t__* murb_used; struct oxu_murb* murb_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxu_murb_free(struct oxu_hcd *oxu, struct oxu_murb *murb)
{
	int index;

	spin_lock(&oxu->mem_lock);

	index = murb - &oxu->murb_pool[0];
	oxu->murb_used[index] = 0;

	spin_unlock(&oxu->mem_lock);
}