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
struct dm_exception_store {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtr ) (struct dm_exception_store*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dm_exception_store*) ; 
 int /*<<< orphan*/  put_type (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct dm_exception_store*) ; 

void dm_exception_store_destroy(struct dm_exception_store *store)
{
	store->type->dtr(store);
	put_type(store->type);
	kfree(store);
}