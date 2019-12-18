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
typedef  int /*<<< orphan*/  val ;
struct socket {TYPE_1__* sk; } ;
struct siw_cep {scalar_t__ state; struct socket* sock; struct siw_cep* listen_cep; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_rmem_alloc; struct siw_cep* sk_user_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SIW_CM_WORK_MPATIMEOUT ; 
 scalar_t__ SIW_EPSTATE_AWAIT_MPAREQ ; 
 scalar_t__ SIW_EPSTATE_LISTENING ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int kernel_accept (struct socket*,struct socket**,int /*<<< orphan*/ ) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct siw_cep* siw_cep_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_cep_get (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_free (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_inuse (struct siw_cep*) ; 
 scalar_t__ siw_cm_alloc_work (struct siw_cep*,int) ; 
 int siw_cm_queue_work (struct siw_cep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,...) ; 
 int siw_proc_mpareq (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_socket_disassoc (struct socket*) ; 
 int siw_tcp_nagle ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static void siw_accept_newconn(struct siw_cep *cep)
{
	struct socket *s = cep->sock;
	struct socket *new_s = NULL;
	struct siw_cep *new_cep = NULL;
	int rv = 0; /* debug only. should disappear */

	if (cep->state != SIW_EPSTATE_LISTENING)
		goto error;

	new_cep = siw_cep_alloc(cep->sdev);
	if (!new_cep)
		goto error;

	/*
	 * 4: Allocate a sufficient number of work elements
	 * to allow concurrent handling of local + peer close
	 * events, MPA header processing + MPA timeout.
	 */
	if (siw_cm_alloc_work(new_cep, 4) != 0)
		goto error;

	/*
	 * Copy saved socket callbacks from listening CEP
	 * and assign new socket with new CEP
	 */
	new_cep->sk_state_change = cep->sk_state_change;
	new_cep->sk_data_ready = cep->sk_data_ready;
	new_cep->sk_write_space = cep->sk_write_space;
	new_cep->sk_error_report = cep->sk_error_report;

	rv = kernel_accept(s, &new_s, O_NONBLOCK);
	if (rv != 0) {
		/*
		 * Connection already aborted by peer..?
		 */
		siw_dbg_cep(cep, "kernel_accept() error: %d\n", rv);
		goto error;
	}
	new_cep->sock = new_s;
	siw_cep_get(new_cep);
	new_s->sk->sk_user_data = new_cep;

	if (siw_tcp_nagle == false) {
		int val = 1;

		rv = kernel_setsockopt(new_s, SOL_TCP, TCP_NODELAY,
				       (char *)&val, sizeof(val));
		if (rv) {
			siw_dbg_cep(cep, "setsockopt NODELAY error: %d\n", rv);
			goto error;
		}
	}
	new_cep->state = SIW_EPSTATE_AWAIT_MPAREQ;

	rv = siw_cm_queue_work(new_cep, SIW_CM_WORK_MPATIMEOUT);
	if (rv)
		goto error;
	/*
	 * See siw_proc_mpareq() etc. for the use of new_cep->listen_cep.
	 */
	new_cep->listen_cep = cep;
	siw_cep_get(cep);

	if (atomic_read(&new_s->sk->sk_rmem_alloc)) {
		/*
		 * MPA REQ already queued
		 */
		siw_dbg_cep(cep, "immediate mpa request\n");

		siw_cep_set_inuse(new_cep);
		rv = siw_proc_mpareq(new_cep);
		siw_cep_set_free(new_cep);

		if (rv != -EAGAIN) {
			siw_cep_put(cep);
			new_cep->listen_cep = NULL;
			if (rv)
				goto error;
		}
	}
	return;

error:
	if (new_cep)
		siw_cep_put(new_cep);

	if (new_s) {
		siw_socket_disassoc(new_s);
		sock_release(new_s);
		new_cep->sock = NULL;
	}
	siw_dbg_cep(cep, "error %d\n", rv);
}