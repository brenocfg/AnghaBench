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
struct tty_struct {struct tracerouter_data* disc_data; } ;
struct tracerouter_data {int /*<<< orphan*/ * kref_tty; } ;
struct TYPE_2__ {scalar_t__ opencalled; int /*<<< orphan*/ * kref_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  routelock ; 
 TYPE_1__* tr_data ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_tracerouter_close(struct tty_struct *tty)
{
	struct tracerouter_data *tptr = tty->disc_data;

	mutex_lock(&routelock);
	WARN_ON(tptr->kref_tty != tr_data->kref_tty);
	tty_driver_flush_buffer(tty);
	tty_kref_put(tr_data->kref_tty);
	tr_data->kref_tty = NULL;
	tr_data->opencalled = 0;
	tty->disc_data = NULL;
	mutex_unlock(&routelock);
}