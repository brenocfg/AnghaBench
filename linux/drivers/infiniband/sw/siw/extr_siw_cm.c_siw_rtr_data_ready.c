#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_suspend; } ;
struct siw_qp {TYPE_2__ rx_stream; } ;
struct siw_cep {int dummy; } ;
struct TYPE_6__ {struct siw_qp* data; } ;
struct TYPE_8__ {int count; TYPE_1__ arg; } ;
typedef  TYPE_3__ read_descriptor_t ;
typedef  int /*<<< orphan*/  rd_desc ;

/* Variables and functions */
 int /*<<< orphan*/  IW_CM_EVENT_ESTABLISHED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_cm_upcall (struct siw_cep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_qp_socket_assoc (struct siw_cep*,struct siw_qp*) ; 
 int /*<<< orphan*/  siw_tcp_rx_data ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 
 struct siw_qp* sk_to_qp (struct sock*) ; 
 int /*<<< orphan*/  tcp_read_sock (struct sock*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void siw_rtr_data_ready(struct sock *sk)
{
	struct siw_cep *cep;
	struct siw_qp *qp = NULL;
	read_descriptor_t rd_desc;

	read_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	if (!cep) {
		WARN(1, "No connection endpoint\n");
		goto out;
	}
	qp = sk_to_qp(sk);

	memset(&rd_desc, 0, sizeof(rd_desc));
	rd_desc.arg.data = qp;
	rd_desc.count = 1;

	tcp_read_sock(sk, &rd_desc, siw_tcp_rx_data);
	/*
	 * Check if first frame was successfully processed.
	 * Signal connection full establishment if yes.
	 * Failed data processing would have already scheduled
	 * connection drop.
	 */
	if (!qp->rx_stream.rx_suspend)
		siw_cm_upcall(cep, IW_CM_EVENT_ESTABLISHED, 0);
out:
	read_unlock(&sk->sk_callback_lock);
	if (qp)
		siw_qp_socket_assoc(cep, qp);
}