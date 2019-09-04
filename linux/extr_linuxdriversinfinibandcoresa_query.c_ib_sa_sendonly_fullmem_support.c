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
typedef  size_t u8 ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  ib; } ;
struct TYPE_4__ {TYPE_1__ data; scalar_t__ valid; } ;
struct ib_sa_port {int /*<<< orphan*/  classport_lock; TYPE_2__ classport_info; } ;
struct ib_sa_device {size_t start_port; struct ib_sa_port* port; } ;
struct ib_sa_client {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_SA_CAP_MASK2_SENDONLY_FULL_MEM_SUPPORT ; 
 scalar_t__ RDMA_CLASS_PORT_INFO_IB ; 
 struct ib_sa_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int ib_get_cpi_capmask2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool ib_sa_sendonly_fullmem_support(struct ib_sa_client *client,
				    struct ib_device *device,
				    u8 port_num)
{
	struct ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	struct ib_sa_port *port;
	bool ret = false;
	unsigned long flags;

	if (!sa_dev)
		return ret;

	port  = &sa_dev->port[port_num - sa_dev->start_port];

	spin_lock_irqsave(&port->classport_lock, flags);
	if ((port->classport_info.valid) &&
	    (port->classport_info.data.type == RDMA_CLASS_PORT_INFO_IB))
		ret = ib_get_cpi_capmask2(&port->classport_info.data.ib)
			& IB_SA_CAP_MASK2_SENDONLY_FULL_MEM_SUPPORT;
	spin_unlock_irqrestore(&port->classport_lock, flags);
	return ret;
}