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
struct detected_devices_node {int /*<<< orphan*/  list; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  all_detected_devices ; 
 int /*<<< orphan*/  detected_devices_mutex ; 
 struct detected_devices_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void md_autodetect_dev(dev_t dev)
{
	struct detected_devices_node *node_detected_dev;

	node_detected_dev = kzalloc(sizeof(*node_detected_dev), GFP_KERNEL);
	if (node_detected_dev) {
		node_detected_dev->dev = dev;
		mutex_lock(&detected_devices_mutex);
		list_add_tail(&node_detected_dev->list, &all_detected_devices);
		mutex_unlock(&detected_devices_mutex);
	}
}