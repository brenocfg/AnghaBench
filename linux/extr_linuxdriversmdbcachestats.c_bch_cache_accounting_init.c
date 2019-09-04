#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct closure {int dummy; } ;
struct TYPE_11__ {scalar_t__ expires; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct cache_accounting {TYPE_5__ timer; int /*<<< orphan*/  cl; TYPE_3__ day; TYPE_2__ hour; TYPE_1__ five_minute; TYPE_4__ total; } ;

/* Variables and functions */
 scalar_t__ accounting_delay ; 
 int /*<<< orphan*/  add_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  bch_stats_ktype ; 
 int /*<<< orphan*/  closure_init (int /*<<< orphan*/ *,struct closure*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scale_accounting ; 
 int /*<<< orphan*/  timer_setup (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bch_cache_accounting_init(struct cache_accounting *acc,
			       struct closure *parent)
{
	kobject_init(&acc->total.kobj,		&bch_stats_ktype);
	kobject_init(&acc->five_minute.kobj,	&bch_stats_ktype);
	kobject_init(&acc->hour.kobj,		&bch_stats_ktype);
	kobject_init(&acc->day.kobj,		&bch_stats_ktype);

	closure_init(&acc->cl, parent);
	timer_setup(&acc->timer, scale_accounting, 0);
	acc->timer.expires	= jiffies + accounting_delay;
	add_timer(&acc->timer);
}