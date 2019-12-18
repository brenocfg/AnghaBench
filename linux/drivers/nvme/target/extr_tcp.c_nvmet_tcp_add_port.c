#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  ss_family; } ;
struct nvmet_tcp_port {int last_cpu; TYPE_3__* sock; TYPE_5__ addr; int /*<<< orphan*/  data_ready; struct nvmet_port* nport; int /*<<< orphan*/  accept_work; } ;
struct TYPE_11__ {int adrfam; int /*<<< orphan*/  portid; int /*<<< orphan*/  trsvcid; int /*<<< orphan*/  traddr; } ;
struct nvmet_port {scalar_t__ inline_data_size; TYPE_2__ disc_addr; struct nvmet_tcp_port* priv; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  __kernel_sa_family_t ;
struct TYPE_12__ {TYPE_1__* sk; } ;
struct TYPE_10__ {int /*<<< orphan*/  sk_data_ready; struct nvmet_tcp_port* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ NVMET_TCP_DEF_INLINE_DATA_SIZE ; 
#define  NVMF_ADDR_FAMILY_IP4 129 
#define  NVMF_ADDR_FAMILY_IP6 128 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int inet_pton_with_scope (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  init_net ; 
 int kernel_bind (TYPE_3__*,struct sockaddr*,int) ; 
 int kernel_listen (TYPE_3__*,int) ; 
 int kernel_setsockopt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct nvmet_tcp_port*) ; 
 struct nvmet_tcp_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_tcp_accept_work ; 
 int /*<<< orphan*/  nvmet_tcp_listen_data_ready ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int sock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  sock_release (TYPE_3__*) ; 

__attribute__((used)) static int nvmet_tcp_add_port(struct nvmet_port *nport)
{
	struct nvmet_tcp_port *port;
	__kernel_sa_family_t af;
	int opt, ret;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	switch (nport->disc_addr.adrfam) {
	case NVMF_ADDR_FAMILY_IP4:
		af = AF_INET;
		break;
	case NVMF_ADDR_FAMILY_IP6:
		af = AF_INET6;
		break;
	default:
		pr_err("address family %d not supported\n",
				nport->disc_addr.adrfam);
		ret = -EINVAL;
		goto err_port;
	}

	ret = inet_pton_with_scope(&init_net, af, nport->disc_addr.traddr,
			nport->disc_addr.trsvcid, &port->addr);
	if (ret) {
		pr_err("malformed ip/port passed: %s:%s\n",
			nport->disc_addr.traddr, nport->disc_addr.trsvcid);
		goto err_port;
	}

	port->nport = nport;
	port->last_cpu = -1;
	INIT_WORK(&port->accept_work, nvmet_tcp_accept_work);
	if (port->nport->inline_data_size < 0)
		port->nport->inline_data_size = NVMET_TCP_DEF_INLINE_DATA_SIZE;

	ret = sock_create(port->addr.ss_family, SOCK_STREAM,
				IPPROTO_TCP, &port->sock);
	if (ret) {
		pr_err("failed to create a socket\n");
		goto err_port;
	}

	port->sock->sk->sk_user_data = port;
	port->data_ready = port->sock->sk->sk_data_ready;
	port->sock->sk->sk_data_ready = nvmet_tcp_listen_data_ready;

	opt = 1;
	ret = kernel_setsockopt(port->sock, IPPROTO_TCP,
			TCP_NODELAY, (char *)&opt, sizeof(opt));
	if (ret) {
		pr_err("failed to set TCP_NODELAY sock opt %d\n", ret);
		goto err_sock;
	}

	ret = kernel_setsockopt(port->sock, SOL_SOCKET, SO_REUSEADDR,
			(char *)&opt, sizeof(opt));
	if (ret) {
		pr_err("failed to set SO_REUSEADDR sock opt %d\n", ret);
		goto err_sock;
	}

	ret = kernel_bind(port->sock, (struct sockaddr *)&port->addr,
			sizeof(port->addr));
	if (ret) {
		pr_err("failed to bind port socket %d\n", ret);
		goto err_sock;
	}

	ret = kernel_listen(port->sock, 128);
	if (ret) {
		pr_err("failed to listen %d on port sock\n", ret);
		goto err_sock;
	}

	nport->priv = port;
	pr_info("enabling port %d (%pISpc)\n",
		le16_to_cpu(nport->disc_addr.portid), &port->addr);

	return 0;

err_sock:
	sock_release(port->sock);
err_port:
	kfree(port);
	return ret;
}