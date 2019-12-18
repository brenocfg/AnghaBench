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
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct tcpci {int controls_vbus; int /*<<< orphan*/  dev; TYPE_1__ tcpc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_named_child_node (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tcpci_parse_config(struct tcpci *tcpci)
{
	tcpci->controls_vbus = true; /* XXX */

	tcpci->tcpc.fwnode = device_get_named_child_node(tcpci->dev,
							 "connector");
	if (!tcpci->tcpc.fwnode) {
		dev_err(tcpci->dev, "Can't find connector node.\n");
		return -EINVAL;
	}

	return 0;
}