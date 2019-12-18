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
struct fwtty_port {TYPE_1__* serial; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 unsigned int MAX_TOTAL_PORTS ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fwtty_port** port_table ; 
 int /*<<< orphan*/  port_table_lock ; 

__attribute__((used)) static struct fwtty_port *fwtty_port_get(unsigned int index)
{
	struct fwtty_port *port;

	if (index >= MAX_TOTAL_PORTS)
		return NULL;

	mutex_lock(&port_table_lock);
	port = port_table[index];
	if (port)
		kref_get(&port->serial->kref);
	mutex_unlock(&port_table_lock);
	return port;
}