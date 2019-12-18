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
struct tty_struct {int dummy; } ;
struct gsm_dlci {int /*<<< orphan*/  state; int /*<<< orphan*/  port; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLCI_CLOSED ; 
 int /*<<< orphan*/  dlci_put (struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_destroy_network (struct gsm_dlci*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsm_dlci_release(struct gsm_dlci *dlci)
{
	struct tty_struct *tty = tty_port_tty_get(&dlci->port);
	if (tty) {
		mutex_lock(&dlci->mutex);
		gsm_destroy_network(dlci);
		mutex_unlock(&dlci->mutex);

		tty_hangup(tty);

		tty_port_tty_set(&dlci->port, NULL);
		tty_kref_put(tty);
	}
	dlci->state = DLCI_CLOSED;
	dlci_put(dlci);
}