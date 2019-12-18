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
struct TYPE_3__ {scalar_t__ sin_port; } ;
struct cxgbi_sock {scalar_t__ state; TYPE_2__* cdev; scalar_t__ dst; TYPE_1__ saddr; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* csk_release_offload_resources ) (struct cxgbi_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ACTIVE_CLOSE_NEEDED ; 
 scalar_t__ CTP_ACTIVE_OPEN ; 
 scalar_t__ CTP_CLOSED ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  cxgbi_inform_iscsi_conn_closing (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,scalar_t__) ; 
 int /*<<< orphan*/  dst_release (scalar_t__) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put_port (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  stub1 (struct cxgbi_sock*) ; 

void cxgbi_sock_closed(struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_set_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED);
	if (csk->state == CTP_ACTIVE_OPEN || csk->state == CTP_CLOSED)
		return;
	if (csk->saddr.sin_port)
		sock_put_port(csk);
	if (csk->dst)
		dst_release(csk->dst);
	csk->cdev->csk_release_offload_resources(csk);
	cxgbi_sock_set_state(csk, CTP_CLOSED);
	cxgbi_inform_iscsi_conn_closing(csk);
	cxgbi_sock_put(csk);
}