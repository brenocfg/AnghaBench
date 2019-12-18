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
struct dvb_adapter {int /*<<< orphan*/  list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvbdev_register_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dvb_unregister_adapter(struct dvb_adapter *adap)
{
	mutex_lock(&dvbdev_register_lock);
	list_del (&adap->list_head);
	mutex_unlock(&dvbdev_register_lock);
	return 0;
}