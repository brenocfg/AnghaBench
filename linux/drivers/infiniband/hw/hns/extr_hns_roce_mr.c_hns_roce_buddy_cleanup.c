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
struct hns_roce_buddy {int max_order; int /*<<< orphan*/ * num_free; int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_buddy_cleanup(struct hns_roce_buddy *buddy)
{
	int i;

	for (i = 0; i <= buddy->max_order; ++i)
		kvfree(buddy->bits[i]);

	kfree(buddy->bits);
	kfree(buddy->num_free);
}