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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct be_eq_obj {TYPE_1__ q; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_eq_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int events_get (struct be_eq_obj*) ; 

__attribute__((used)) static void be_eq_clean(struct be_eq_obj *eqo)
{
	int num = events_get(eqo);

	be_eq_notify(eqo->adapter, eqo->q.id, false, true, num, 0);
}