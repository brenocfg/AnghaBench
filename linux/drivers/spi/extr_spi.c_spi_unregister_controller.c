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
struct spi_controller {int bus_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; scalar_t__ queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister ; 
 int /*<<< orphan*/  board_lock ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 struct spi_controller* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ spi_destroy_queue (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_master_idr ; 

void spi_unregister_controller(struct spi_controller *ctlr)
{
	struct spi_controller *found;
	int id = ctlr->bus_num;

	/* First make sure that this controller was ever added */
	mutex_lock(&board_lock);
	found = idr_find(&spi_master_idr, id);
	mutex_unlock(&board_lock);
	if (ctlr->queued) {
		if (spi_destroy_queue(ctlr))
			dev_err(&ctlr->dev, "queue remove failed\n");
	}
	mutex_lock(&board_lock);
	list_del(&ctlr->list);
	mutex_unlock(&board_lock);

	device_for_each_child(&ctlr->dev, NULL, __unregister);
	device_unregister(&ctlr->dev);
	/* free bus id */
	mutex_lock(&board_lock);
	if (found == ctlr)
		idr_remove(&spi_master_idr, id);
	mutex_unlock(&board_lock);
}