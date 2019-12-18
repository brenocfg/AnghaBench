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
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtr ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dm_dirty_log*) ; 
 int /*<<< orphan*/  put_type (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct dm_dirty_log*) ; 

void dm_dirty_log_destroy(struct dm_dirty_log *log)
{
	log->type->dtr(log);
	put_type(log->type);
	kfree(log);
}