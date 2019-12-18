#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct typec_altmode_desc {scalar_t__ svid; } ;
struct typec_altmode {int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int revision; int pd_revision; int /*<<< orphan*/  type; int /*<<< orphan*/  port_type_set; int /*<<< orphan*/  try_role; int /*<<< orphan*/  vconn_set; int /*<<< orphan*/  pr_set; int /*<<< orphan*/  dr_set; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  prefer_role; } ;
struct TYPE_4__ {int /*<<< orphan*/ * identity; } ;
struct tcpm_port {int /*<<< orphan*/  wq; struct typec_altmode* role_sw; int /*<<< orphan*/  lock; struct typec_altmode** port_altmode; struct typec_altmode* typec_port; TYPE_2__ typec_caps; struct device* dev; int /*<<< orphan*/  port_type; int /*<<< orphan*/  partner_ident; TYPE_1__ partner_desc; int /*<<< orphan*/  try_role; int /*<<< orphan*/  pps_complete; int /*<<< orphan*/  swap_complete; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  pd_event_lock; int /*<<< orphan*/  event_work; int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  state_machine; int /*<<< orphan*/  swap_lock; struct tcpc_dev* tcpc; } ;
struct tcpc_dev {TYPE_3__* config; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  pd_transmit; int /*<<< orphan*/  set_roles; int /*<<< orphan*/  set_pd_rx; int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  set_vconn; int /*<<< orphan*/  set_polarity; int /*<<< orphan*/  get_cc; int /*<<< orphan*/  set_cc; int /*<<< orphan*/  get_vbus; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct typec_altmode_desc* alt_modes; int /*<<< orphan*/  try_role_hw; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct typec_altmode**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct tcpm_port* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct typec_altmode*) ; 
 int PTR_ERR (struct typec_altmode*) ; 
 int /*<<< orphan*/  TYPEC_NO_PREFERRED_ROLE ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct tcpm_port* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_tcpm_psy_register (struct tcpm_port*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_altmode_ops ; 
 int tcpm_copy_caps (struct tcpm_port*,TYPE_3__*) ; 
 int /*<<< orphan*/  tcpm_debugfs_exit (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_debugfs_init (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_dr_set ; 
 int tcpm_fw_get_caps (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_init (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tcpm_pd_event_handler ; 
 int /*<<< orphan*/  tcpm_port_type_set ; 
 int /*<<< orphan*/  tcpm_pr_set ; 
 int /*<<< orphan*/  tcpm_state_machine_work ; 
 int /*<<< orphan*/  tcpm_try_role ; 
 int /*<<< orphan*/  tcpm_vconn_set ; 
 int /*<<< orphan*/  typec_altmode_set_drvdata (struct typec_altmode*,struct tcpm_port*) ; 
 struct typec_altmode* typec_port_register_altmode (struct typec_altmode*,struct typec_altmode_desc const*) ; 
 struct typec_altmode* typec_register_port (struct device*,TYPE_2__*) ; 
 struct typec_altmode* usb_role_switch_get (struct device*) ; 
 int /*<<< orphan*/  usb_role_switch_put (struct typec_altmode*) ; 
 int /*<<< orphan*/  vdm_state_machine_work ; 

struct tcpm_port *tcpm_register_port(struct device *dev, struct tcpc_dev *tcpc)
{
	struct tcpm_port *port;
	int i, err;

	if (!dev || !tcpc ||
	    !tcpc->get_vbus || !tcpc->set_cc || !tcpc->get_cc ||
	    !tcpc->set_polarity || !tcpc->set_vconn || !tcpc->set_vbus ||
	    !tcpc->set_pd_rx || !tcpc->set_roles || !tcpc->pd_transmit)
		return ERR_PTR(-EINVAL);

	port = devm_kzalloc(dev, sizeof(*port), GFP_KERNEL);
	if (!port)
		return ERR_PTR(-ENOMEM);

	port->dev = dev;
	port->tcpc = tcpc;

	mutex_init(&port->lock);
	mutex_init(&port->swap_lock);

	port->wq = create_singlethread_workqueue(dev_name(dev));
	if (!port->wq)
		return ERR_PTR(-ENOMEM);
	INIT_DELAYED_WORK(&port->state_machine, tcpm_state_machine_work);
	INIT_DELAYED_WORK(&port->vdm_state_machine, vdm_state_machine_work);
	INIT_WORK(&port->event_work, tcpm_pd_event_handler);

	spin_lock_init(&port->pd_event_lock);

	init_completion(&port->tx_complete);
	init_completion(&port->swap_complete);
	init_completion(&port->pps_complete);
	tcpm_debugfs_init(port);

	err = tcpm_fw_get_caps(port, tcpc->fwnode);
	if ((err < 0) && tcpc->config)
		err = tcpm_copy_caps(port, tcpc->config);
	if (err < 0)
		goto out_destroy_wq;

	if (!tcpc->config || !tcpc->config->try_role_hw)
		port->try_role = port->typec_caps.prefer_role;
	else
		port->try_role = TYPEC_NO_PREFERRED_ROLE;

	port->typec_caps.fwnode = tcpc->fwnode;
	port->typec_caps.revision = 0x0120;	/* Type-C spec release 1.2 */
	port->typec_caps.pd_revision = 0x0300;	/* USB-PD spec release 3.0 */
	port->typec_caps.dr_set = tcpm_dr_set;
	port->typec_caps.pr_set = tcpm_pr_set;
	port->typec_caps.vconn_set = tcpm_vconn_set;
	port->typec_caps.try_role = tcpm_try_role;
	port->typec_caps.port_type_set = tcpm_port_type_set;

	port->partner_desc.identity = &port->partner_ident;
	port->port_type = port->typec_caps.type;

	port->role_sw = usb_role_switch_get(port->dev);
	if (IS_ERR(port->role_sw)) {
		err = PTR_ERR(port->role_sw);
		goto out_destroy_wq;
	}

	err = devm_tcpm_psy_register(port);
	if (err)
		goto out_role_sw_put;

	port->typec_port = typec_register_port(port->dev, &port->typec_caps);
	if (IS_ERR(port->typec_port)) {
		err = PTR_ERR(port->typec_port);
		goto out_role_sw_put;
	}

	if (tcpc->config && tcpc->config->alt_modes) {
		const struct typec_altmode_desc *paltmode = tcpc->config->alt_modes;

		i = 0;
		while (paltmode->svid && i < ARRAY_SIZE(port->port_altmode)) {
			struct typec_altmode *alt;

			alt = typec_port_register_altmode(port->typec_port,
							  paltmode);
			if (IS_ERR(alt)) {
				tcpm_log(port,
					 "%s: failed to register port alternate mode 0x%x",
					 dev_name(dev), paltmode->svid);
				break;
			}
			typec_altmode_set_drvdata(alt, port);
			alt->ops = &tcpm_altmode_ops;
			port->port_altmode[i] = alt;
			i++;
			paltmode++;
		}
	}

	mutex_lock(&port->lock);
	tcpm_init(port);
	mutex_unlock(&port->lock);

	tcpm_log(port, "%s: registered", dev_name(dev));
	return port;

out_role_sw_put:
	usb_role_switch_put(port->role_sw);
out_destroy_wq:
	tcpm_debugfs_exit(port);
	destroy_workqueue(port->wq);
	return ERR_PTR(err);
}