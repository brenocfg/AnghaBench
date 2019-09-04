#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct cache_accounting {int /*<<< orphan*/  cl; int /*<<< orphan*/  timer; int /*<<< orphan*/  closing; TYPE_4__ day; TYPE_3__ hour; TYPE_2__ five_minute; TYPE_1__ total; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  closure_return (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

void bch_cache_accounting_destroy(struct cache_accounting *acc)
{
	kobject_put(&acc->total.kobj);
	kobject_put(&acc->five_minute.kobj);
	kobject_put(&acc->hour.kobj);
	kobject_put(&acc->day.kobj);

	atomic_set(&acc->closing, 1);
	if (del_timer_sync(&acc->timer))
		closure_return(&acc->cl);
}