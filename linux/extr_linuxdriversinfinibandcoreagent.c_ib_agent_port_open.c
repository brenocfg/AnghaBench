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
struct ib_device {int dummy; } ;
struct ib_agent_port_private {void** agent; int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_SMI ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  agent_send_handler ; 
 int /*<<< orphan*/  ib_agent_port_list ; 
 int /*<<< orphan*/  ib_agent_port_list_lock ; 
 void* ib_register_mad_agent (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (void*) ; 
 int /*<<< orphan*/  kfree (struct ib_agent_port_private*) ; 
 struct ib_agent_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_cap_ib_smi (struct ib_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_agent_port_open(struct ib_device *device, int port_num)
{
	struct ib_agent_port_private *port_priv;
	unsigned long flags;
	int ret;

	/* Create new device info */
	port_priv = kzalloc(sizeof *port_priv, GFP_KERNEL);
	if (!port_priv) {
		ret = -ENOMEM;
		goto error1;
	}

	if (rdma_cap_ib_smi(device, port_num)) {
		/* Obtain send only MAD agent for SMI QP */
		port_priv->agent[0] = ib_register_mad_agent(device, port_num,
							    IB_QPT_SMI, NULL, 0,
							    &agent_send_handler,
							    NULL, NULL, 0);
		if (IS_ERR(port_priv->agent[0])) {
			ret = PTR_ERR(port_priv->agent[0]);
			goto error2;
		}
	}

	/* Obtain send only MAD agent for GSI QP */
	port_priv->agent[1] = ib_register_mad_agent(device, port_num,
						    IB_QPT_GSI, NULL, 0,
						    &agent_send_handler,
						    NULL, NULL, 0);
	if (IS_ERR(port_priv->agent[1])) {
		ret = PTR_ERR(port_priv->agent[1]);
		goto error3;
	}

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	list_add_tail(&port_priv->port_list, &ib_agent_port_list);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);

	return 0;

error3:
	if (port_priv->agent[0])
		ib_unregister_mad_agent(port_priv->agent[0]);
error2:
	kfree(port_priv);
error1:
	return ret;
}