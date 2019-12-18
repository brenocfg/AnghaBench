#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_send_buf {int dummy; } ;
struct ib_mad_recv_wc {TYPE_1__* wc; } ;
struct cm_port {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkey_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_MGMT_BASE_VERSION ; 
 int /*<<< orphan*/  IB_MGMT_MAD_DATA ; 
 int /*<<< orphan*/  IB_MGMT_MAD_HDR ; 
 struct ib_mad_send_buf* ib_create_send_mad (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_mad_send_buf *cm_alloc_response_msg_no_ah(struct cm_port *port,
							   struct ib_mad_recv_wc *mad_recv_wc)
{
	return ib_create_send_mad(port->mad_agent, 1, mad_recv_wc->wc->pkey_index,
				  0, IB_MGMT_MAD_HDR, IB_MGMT_MAD_DATA,
				  GFP_ATOMIC,
				  IB_MGMT_BASE_VERSION);
}