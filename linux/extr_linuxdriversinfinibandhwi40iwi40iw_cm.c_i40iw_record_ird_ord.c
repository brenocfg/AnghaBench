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
typedef  scalar_t__ u32 ;
struct i40iw_cm_node {scalar_t__ send_rdma0_op; scalar_t__ ord_size; scalar_t__ ird_size; } ;

/* Variables and functions */
 scalar_t__ I40IW_MAX_IRD_SIZE ; 
 scalar_t__ I40IW_MAX_ORD_SIZE ; 
 scalar_t__ SEND_RDMA_READ_ZERO ; 

__attribute__((used)) static void i40iw_record_ird_ord(struct i40iw_cm_node *cm_node, u32 conn_ird,
				 u32 conn_ord)
{
	if (conn_ird > I40IW_MAX_IRD_SIZE)
		conn_ird = I40IW_MAX_IRD_SIZE;

	if (conn_ord > I40IW_MAX_ORD_SIZE)
		conn_ord = I40IW_MAX_ORD_SIZE;
	else if (!conn_ord && cm_node->send_rdma0_op == SEND_RDMA_READ_ZERO)
		conn_ord = 1;

	cm_node->ird_size = conn_ird;
	cm_node->ord_size = conn_ord;
}