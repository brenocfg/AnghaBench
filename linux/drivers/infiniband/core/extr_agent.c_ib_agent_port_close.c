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
struct ib_device {int /*<<< orphan*/  dev; } ;
struct ib_agent_port_private {scalar_t__* agent; int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ib_agent_port_private* __ib_get_agent_port (struct ib_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ib_agent_port_list_lock ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ib_agent_port_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_agent_port_close(struct ib_device *device, int port_num)
{
	struct ib_agent_port_private *port_priv;
	unsigned long flags;

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	port_priv = __ib_get_agent_port(device, port_num);
	if (port_priv == NULL) {
		spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);
		dev_err(&device->dev, "Port %d not found\n", port_num);
		return -ENODEV;
	}
	list_del(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);

	ib_unregister_mad_agent(port_priv->agent[1]);
	if (port_priv->agent[0])
		ib_unregister_mad_agent(port_priv->agent[0]);

	kfree(port_priv);
	return 0;
}