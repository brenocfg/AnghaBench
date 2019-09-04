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
struct ib_mad_port_private {int /*<<< orphan*/ * qp_info; int /*<<< orphan*/  cq; int /*<<< orphan*/  pd; int /*<<< orphan*/  wq; int /*<<< orphan*/  port_list; } ;
struct ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ib_mad_port_private* __ib_get_mad_port (struct ib_device*,int) ; 
 int /*<<< orphan*/  cleanup_recv_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_mad_qp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mad_port_list_lock ; 
 int /*<<< orphan*/  kfree (struct ib_mad_port_private*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ib_mad_port_close(struct ib_device *device, int port_num)
{
	struct ib_mad_port_private *port_priv;
	unsigned long flags;

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	port_priv = __ib_get_mad_port(device, port_num);
	if (port_priv == NULL) {
		spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);
		dev_err(&device->dev, "Port %d not found\n", port_num);
		return -ENODEV;
	}
	list_del_init(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	destroy_workqueue(port_priv->wq);
	destroy_mad_qp(&port_priv->qp_info[1]);
	destroy_mad_qp(&port_priv->qp_info[0]);
	ib_dealloc_pd(port_priv->pd);
	ib_free_cq(port_priv->cq);
	cleanup_recv_queue(&port_priv->qp_info[1]);
	cleanup_recv_queue(&port_priv->qp_info[0]);
	/* XXX: Handle deallocation of MAD registration tables */

	kfree(port_priv);

	return 0;
}