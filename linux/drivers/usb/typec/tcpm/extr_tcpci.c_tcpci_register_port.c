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
struct tcpci_data {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  pd_transmit; int /*<<< orphan*/  set_roles; int /*<<< orphan*/  set_pd_rx; int /*<<< orphan*/  start_toggling; int /*<<< orphan*/  set_vconn; int /*<<< orphan*/  set_polarity; int /*<<< orphan*/  get_cc; int /*<<< orphan*/  set_cc; int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  get_vbus; int /*<<< orphan*/  init; } ;
struct tcpci {int /*<<< orphan*/  port; TYPE_1__ tcpc; struct device* dev; int /*<<< orphan*/  regmap; struct tcpci_data* data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tcpci* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct tcpci* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct tcpci* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpci_get_cc ; 
 int /*<<< orphan*/  tcpci_get_vbus ; 
 int /*<<< orphan*/  tcpci_init ; 
 int tcpci_parse_config (struct tcpci*) ; 
 int /*<<< orphan*/  tcpci_pd_transmit ; 
 int /*<<< orphan*/  tcpci_set_cc ; 
 int /*<<< orphan*/  tcpci_set_pd_rx ; 
 int /*<<< orphan*/  tcpci_set_polarity ; 
 int /*<<< orphan*/  tcpci_set_roles ; 
 int /*<<< orphan*/  tcpci_set_vbus ; 
 int /*<<< orphan*/  tcpci_set_vconn ; 
 int /*<<< orphan*/  tcpci_start_toggling ; 
 int /*<<< orphan*/  tcpm_register_port (struct device*,TYPE_1__*) ; 

struct tcpci *tcpci_register_port(struct device *dev, struct tcpci_data *data)
{
	struct tcpci *tcpci;
	int err;

	tcpci = devm_kzalloc(dev, sizeof(*tcpci), GFP_KERNEL);
	if (!tcpci)
		return ERR_PTR(-ENOMEM);

	tcpci->dev = dev;
	tcpci->data = data;
	tcpci->regmap = data->regmap;

	tcpci->tcpc.init = tcpci_init;
	tcpci->tcpc.get_vbus = tcpci_get_vbus;
	tcpci->tcpc.set_vbus = tcpci_set_vbus;
	tcpci->tcpc.set_cc = tcpci_set_cc;
	tcpci->tcpc.get_cc = tcpci_get_cc;
	tcpci->tcpc.set_polarity = tcpci_set_polarity;
	tcpci->tcpc.set_vconn = tcpci_set_vconn;
	tcpci->tcpc.start_toggling = tcpci_start_toggling;

	tcpci->tcpc.set_pd_rx = tcpci_set_pd_rx;
	tcpci->tcpc.set_roles = tcpci_set_roles;
	tcpci->tcpc.pd_transmit = tcpci_pd_transmit;

	err = tcpci_parse_config(tcpci);
	if (err < 0)
		return ERR_PTR(err);

	tcpci->port = tcpm_register_port(tcpci->dev, &tcpci->tcpc);
	if (IS_ERR(tcpci->port))
		return ERR_CAST(tcpci->port);

	return tcpci;
}