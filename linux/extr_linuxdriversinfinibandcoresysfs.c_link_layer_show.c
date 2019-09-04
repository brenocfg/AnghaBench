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
struct port_attribute {int dummy; } ;
struct ib_port {int /*<<< orphan*/  port_num; int /*<<< orphan*/  ibdev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  IB_LINK_LAYER_ETHERNET 129 
#define  IB_LINK_LAYER_INFINIBAND 128 
 int rdma_port_get_link_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t link_layer_show(struct ib_port *p, struct port_attribute *unused,
			       char *buf)
{
	switch (rdma_port_get_link_layer(p->ibdev, p->port_num)) {
	case IB_LINK_LAYER_INFINIBAND:
		return sprintf(buf, "%s\n", "InfiniBand");
	case IB_LINK_LAYER_ETHERNET:
		return sprintf(buf, "%s\n", "Ethernet");
	default:
		return sprintf(buf, "%s\n", "Unknown");
	}
}