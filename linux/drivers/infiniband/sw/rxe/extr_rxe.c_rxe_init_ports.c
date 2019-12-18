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
struct TYPE_4__ {int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  gid_tbl_len; } ;
struct rxe_port {int* pkey_tbl; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  port_guid; TYPE_2__ attr; } ;
struct rxe_dev {TYPE_1__* ndev; struct rxe_port port; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  addrconf_addr_eui48 (unsigned char*,int /*<<< orphan*/ ) ; 
 int* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_init_port_param (struct rxe_port*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxe_init_ports(struct rxe_dev *rxe)
{
	struct rxe_port *port = &rxe->port;

	rxe_init_port_param(port);

	if (!port->attr.pkey_tbl_len || !port->attr.gid_tbl_len)
		return -EINVAL;

	port->pkey_tbl = kcalloc(port->attr.pkey_tbl_len,
			sizeof(*port->pkey_tbl), GFP_KERNEL);

	if (!port->pkey_tbl)
		return -ENOMEM;

	port->pkey_tbl[0] = 0xffff;
	addrconf_addr_eui48((unsigned char *)&port->port_guid,
			    rxe->ndev->dev_addr);

	spin_lock_init(&port->port_lock);

	return 0;
}