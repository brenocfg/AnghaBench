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
struct socket {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int (* create ) (struct net*,struct socket*,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  PF_PPPOX ; 
 int PX_MAX_PROTO ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 TYPE_1__** pppox_protos ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct net*,struct socket*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppox_create(struct net *net, struct socket *sock, int protocol,
			int kern)
{
	int rc = -EPROTOTYPE;

	if (protocol < 0 || protocol > PX_MAX_PROTO)
		goto out;

	rc = -EPROTONOSUPPORT;
	if (!pppox_protos[protocol])
		request_module("net-pf-%d-proto-%d", PF_PPPOX, protocol);
	if (!pppox_protos[protocol] ||
	    !try_module_get(pppox_protos[protocol]->owner))
		goto out;

	rc = pppox_protos[protocol]->create(net, sock, kern);

	module_put(pppox_protos[protocol]->owner);
out:
	return rc;
}