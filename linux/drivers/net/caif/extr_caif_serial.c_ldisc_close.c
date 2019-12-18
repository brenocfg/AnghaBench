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
struct tty_struct {struct ser_device* disc_data; } ;
struct ser_device {int /*<<< orphan*/  node; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ser_lock ; 
 int /*<<< orphan*/  ser_release_list ; 
 int /*<<< orphan*/  ser_release_work ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ldisc_close(struct tty_struct *tty)
{
	struct ser_device *ser = tty->disc_data;

	tty_kref_put(ser->tty);

	spin_lock(&ser_lock);
	list_move(&ser->node, &ser_release_list);
	spin_unlock(&ser_lock);
	schedule_work(&ser_release_work);
}