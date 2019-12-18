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
struct parport {struct parport** slaves; int /*<<< orphan*/  list; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dead_ops ; 
 int /*<<< orphan*/  detach_driver_chain (struct parport*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_daisy_fini (struct parport*) ; 
 int /*<<< orphan*/  parport_proc_unregister (struct parport*) ; 
 int /*<<< orphan*/  parport_put_port (struct parport*) ; 
 int /*<<< orphan*/  parportlist_lock ; 
 int /*<<< orphan*/  registration_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void parport_remove_port(struct parport *port)
{
	int i;

	mutex_lock(&registration_lock);

	/* Spread the word. */
	detach_driver_chain(port);

#ifdef CONFIG_PARPORT_1284
	/* Forget the IEEE1284.3 topology of the port. */
	parport_daisy_fini(port);
	for (i = 1; i < 3; i++) {
		struct parport *slave = port->slaves[i-1];
		if (!slave)
			continue;
		detach_driver_chain(slave);
		parport_daisy_fini(slave);
	}
#endif

	port->ops = &dead_ops;
	spin_lock(&parportlist_lock);
	list_del_init(&port->list);
	for (i = 1; i < 3; i++) {
		struct parport *slave = port->slaves[i-1];
		if (slave)
			list_del_init(&slave->list);
	}
	spin_unlock(&parportlist_lock);

	mutex_unlock(&registration_lock);

	parport_proc_unregister(port);

	for (i = 1; i < 3; i++) {
		struct parport *slave = port->slaves[i-1];
		if (slave)
			parport_put_port(slave);
	}
}