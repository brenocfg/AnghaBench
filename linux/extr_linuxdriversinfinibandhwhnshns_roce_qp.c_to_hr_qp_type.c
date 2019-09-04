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

/* Variables and functions */
 int IB_QPT_GSI ; 
 int IB_QPT_RC ; 
 int IB_QPT_UC ; 
 int IB_QPT_UD ; 
 int SERV_TYPE_RC ; 
 int SERV_TYPE_UC ; 
 int SERV_TYPE_UD ; 

int to_hr_qp_type(int qp_type)
{
	int transport_type;

	if (qp_type == IB_QPT_RC)
		transport_type = SERV_TYPE_RC;
	else if (qp_type == IB_QPT_UC)
		transport_type = SERV_TYPE_UC;
	else if (qp_type == IB_QPT_UD)
		transport_type = SERV_TYPE_UD;
	else if (qp_type == IB_QPT_GSI)
		transport_type = SERV_TYPE_UD;
	else
		transport_type = -1;

	return transport_type;
}