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
struct domain_device {int /*<<< orphan*/  disco_list_node; int /*<<< orphan*/  rphy; int /*<<< orphan*/  state; } ;
struct asd_sas_port {int /*<<< orphan*/  destroy_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_DEV_DESTROY ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_rphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_rphy_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_unregister_common_dev (struct asd_sas_port*,struct domain_device*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sas_unregister_dev(struct asd_sas_port *port, struct domain_device *dev)
{
	if (!test_bit(SAS_DEV_DESTROY, &dev->state) &&
	    !list_empty(&dev->disco_list_node)) {
		/* this rphy never saw sas_rphy_add */
		list_del_init(&dev->disco_list_node);
		sas_rphy_free(dev->rphy);
		sas_unregister_common_dev(port, dev);
		return;
	}

	if (!test_and_set_bit(SAS_DEV_DESTROY, &dev->state)) {
		sas_rphy_unlink(dev->rphy);
		list_move_tail(&dev->disco_list_node, &port->destroy_list);
	}
}