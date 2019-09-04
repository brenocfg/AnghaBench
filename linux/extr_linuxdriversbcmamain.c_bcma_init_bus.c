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
struct bcma_bus {scalar_t__ nr_cores; int /*<<< orphan*/  cores; scalar_t__ num; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_bus_next_num ; 
 int /*<<< orphan*/  bcma_buses_mutex ; 
 int /*<<< orphan*/  bcma_detect_chip (struct bcma_bus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void bcma_init_bus(struct bcma_bus *bus)
{
	mutex_lock(&bcma_buses_mutex);
	bus->num = bcma_bus_next_num++;
	mutex_unlock(&bcma_buses_mutex);

	INIT_LIST_HEAD(&bus->cores);
	bus->nr_cores = 0;

	bcma_detect_chip(bus);
}