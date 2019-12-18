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
struct ntb_dev {int topo; } ;

/* Variables and functions */
 int EINVAL ; 
 int NTB_PORT_PRI_USD ; 
 int NTB_PORT_SEC_DSD ; 
#define  NTB_TOPO_B2B_DSD 131 
#define  NTB_TOPO_B2B_USD 130 
#define  NTB_TOPO_PRI 129 
#define  NTB_TOPO_SEC 128 

int ntb_default_port_number(struct ntb_dev *ntb)
{
	switch (ntb->topo) {
	case NTB_TOPO_PRI:
	case NTB_TOPO_B2B_USD:
		return NTB_PORT_PRI_USD;
	case NTB_TOPO_SEC:
	case NTB_TOPO_B2B_DSD:
		return NTB_PORT_SEC_DSD;
	default:
		break;
	}

	return -EINVAL;
}