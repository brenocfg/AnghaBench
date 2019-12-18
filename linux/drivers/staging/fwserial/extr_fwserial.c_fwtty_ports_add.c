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
struct fw_serial {TYPE_1__** ports; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_TOTAL_PORTS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_ports ; 
 TYPE_1__** port_table ; 
 scalar_t__ port_table_corrupt ; 
 int /*<<< orphan*/  port_table_lock ; 

__attribute__((used)) static int fwtty_ports_add(struct fw_serial *serial)
{
	int err = -EBUSY;
	int i, j;

	if (port_table_corrupt)
		return err;

	mutex_lock(&port_table_lock);
	for (i = 0; i + num_ports <= MAX_TOTAL_PORTS; i += num_ports) {
		if (!port_table[i]) {
			for (j = 0; j < num_ports; ++i, ++j) {
				serial->ports[j]->index = i;
				port_table[i] = serial->ports[j];
			}
			err = 0;
			break;
		}
	}
	mutex_unlock(&port_table_lock);
	return err;
}