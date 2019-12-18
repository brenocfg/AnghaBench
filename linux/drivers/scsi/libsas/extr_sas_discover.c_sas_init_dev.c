#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  children; } ;
struct TYPE_3__ {int /*<<< orphan*/  eh_list_node; } ;
struct domain_device {int dev_type; TYPE_2__ ex_dev; TYPE_1__ ssp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  SAS_EDGE_EXPANDER_DEVICE 130 
#define  SAS_END_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void sas_init_dev(struct domain_device *dev)
{
	switch (dev->dev_type) {
	case SAS_END_DEVICE:
		INIT_LIST_HEAD(&dev->ssp_dev.eh_list_node);
		break;
	case SAS_EDGE_EXPANDER_DEVICE:
	case SAS_FANOUT_EXPANDER_DEVICE:
		INIT_LIST_HEAD(&dev->ex_dev.children);
		mutex_init(&dev->ex_dev.cmd_mutex);
		break;
	default:
		break;
	}
}