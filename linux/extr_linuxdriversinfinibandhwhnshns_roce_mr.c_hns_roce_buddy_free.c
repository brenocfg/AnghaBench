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
struct hns_roce_buddy {int /*<<< orphan*/  lock; int /*<<< orphan*/ * num_free; int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_buddy_free(struct hns_roce_buddy *buddy, unsigned long seg,
				int order)
{
	seg >>= order;

	spin_lock(&buddy->lock);

	while (test_bit(seg ^ 1, buddy->bits[order])) {
		clear_bit(seg ^ 1, buddy->bits[order]);
		--buddy->num_free[order];
		seg >>= 1;
		++order;
	}

	set_bit(seg, buddy->bits[order]);
	++buddy->num_free[order];

	spin_unlock(&buddy->lock);
}