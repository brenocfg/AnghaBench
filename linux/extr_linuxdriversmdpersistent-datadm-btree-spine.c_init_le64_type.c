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
struct dm_transaction_manager {int dummy; } ;
struct dm_btree_value_type {int size; int /*<<< orphan*/  equal; int /*<<< orphan*/  dec; int /*<<< orphan*/  inc; struct dm_transaction_manager* context; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  le64_dec ; 
 int /*<<< orphan*/  le64_equal ; 
 int /*<<< orphan*/  le64_inc ; 

void init_le64_type(struct dm_transaction_manager *tm,
		    struct dm_btree_value_type *vt)
{
	vt->context = tm;
	vt->size = sizeof(__le64);
	vt->inc = le64_inc;
	vt->dec = le64_dec;
	vt->equal = le64_equal;
}