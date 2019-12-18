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
struct socket {TYPE_1__* ops; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct siw_device {int dummy; } ;
struct siw_cep {int /*<<< orphan*/  state; int /*<<< orphan*/ * sock; struct iw_cm_id* cm_id; int /*<<< orphan*/  listenq; } ;
struct list_head {int dummy; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  device; scalar_t__ provider_data; int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;} ;
typedef  int /*<<< orphan*/  s_val ;
struct TYPE_2__ {int (* bind ) (struct socket*,struct sockaddr*,int) ;int (* listen ) (struct socket*,int) ;} ;

/* Variables and functions */
 int AF_INET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SIW_EPSTATE_CLOSED ; 
 int /*<<< orphan*/  SIW_EPSTATE_LISTENING ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct siw_cep* siw_cep_alloc (struct siw_device*) ; 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_free (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_inuse (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_socket_assoc (struct siw_cep*,struct socket*) ; 
 int siw_cm_alloc_work (struct siw_cep*,int) ; 
 int /*<<< orphan*/  siw_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  siw_socket_disassoc (struct socket*) ; 
 int sock_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 
 int stub2 (struct socket*,int) ; 
 int /*<<< orphan*/  stub3 (struct iw_cm_id*) ; 
 int /*<<< orphan*/  stub4 (struct iw_cm_id*) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siw_listen_address(struct iw_cm_id *id, int backlog,
			      struct sockaddr *laddr, int addr_family)
{
	struct socket *s;
	struct siw_cep *cep = NULL;
	struct siw_device *sdev = to_siw_dev(id->device);
	int rv = 0, s_val;

	rv = sock_create(addr_family, SOCK_STREAM, IPPROTO_TCP, &s);
	if (rv < 0)
		return rv;

	/*
	 * Allow binding local port when still in TIME_WAIT from last close.
	 */
	s_val = 1;
	rv = kernel_setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&s_val,
			       sizeof(s_val));
	if (rv) {
		siw_dbg(id->device, "setsockopt error: %d\n", rv);
		goto error;
	}
	rv = s->ops->bind(s, laddr, addr_family == AF_INET ?
				    sizeof(struct sockaddr_in) :
				    sizeof(struct sockaddr_in6));
	if (rv) {
		siw_dbg(id->device, "socket bind error: %d\n", rv);
		goto error;
	}
	cep = siw_cep_alloc(sdev);
	if (!cep) {
		rv = -ENOMEM;
		goto error;
	}
	siw_cep_socket_assoc(cep, s);

	rv = siw_cm_alloc_work(cep, backlog);
	if (rv) {
		siw_dbg(id->device,
			"alloc_work error %d, backlog %d\n",
			rv, backlog);
		goto error;
	}
	rv = s->ops->listen(s, backlog);
	if (rv) {
		siw_dbg(id->device, "listen error %d\n", rv);
		goto error;
	}
	cep->cm_id = id;
	id->add_ref(id);

	/*
	 * In case of a wildcard rdma_listen on a multi-homed device,
	 * a listener's IWCM id is associated with more than one listening CEP.
	 *
	 * We currently use id->provider_data in three different ways:
	 *
	 * o For a listener's IWCM id, id->provider_data points to
	 *   the list_head of the list of listening CEPs.
	 *   Uses: siw_create_listen(), siw_destroy_listen()
	 *
	 * o For each accepted passive-side IWCM id, id->provider_data
	 *   points to the CEP itself. This is a consequence of
	 *   - siw_cm_upcall() setting event.provider_data = cep and
	 *   - the IWCM's cm_conn_req_handler() setting provider_data of the
	 *     new passive-side IWCM id equal to event.provider_data
	 *   Uses: siw_accept(), siw_reject()
	 *
	 * o For an active-side IWCM id, id->provider_data is not used at all.
	 *
	 */
	if (!id->provider_data) {
		id->provider_data =
			kmalloc(sizeof(struct list_head), GFP_KERNEL);
		if (!id->provider_data) {
			rv = -ENOMEM;
			goto error;
		}
		INIT_LIST_HEAD((struct list_head *)id->provider_data);
	}
	list_add_tail(&cep->listenq, (struct list_head *)id->provider_data);
	cep->state = SIW_EPSTATE_LISTENING;

	if (addr_family == AF_INET)
		siw_dbg(id->device, "Listen at laddr %pI4 %u\n",
			&(((struct sockaddr_in *)laddr)->sin_addr),
			((struct sockaddr_in *)laddr)->sin_port);
	else
		siw_dbg(id->device, "Listen at laddr %pI6 %u\n",
			&(((struct sockaddr_in6 *)laddr)->sin6_addr),
			((struct sockaddr_in6 *)laddr)->sin6_port);

	return 0;

error:
	siw_dbg(id->device, "failed: %d\n", rv);

	if (cep) {
		siw_cep_set_inuse(cep);

		if (cep->cm_id) {
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = NULL;
		}
		cep->sock = NULL;
		siw_socket_disassoc(s);
		cep->state = SIW_EPSTATE_CLOSED;

		siw_cep_set_free(cep);
		siw_cep_put(cep);
	}
	sock_release(s);

	return rv;
}