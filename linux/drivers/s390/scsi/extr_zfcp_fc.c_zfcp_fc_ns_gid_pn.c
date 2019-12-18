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
struct zfcp_port {struct zfcp_adapter* adapter; } ;
struct zfcp_fc_req {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gid_pn; } ;
struct zfcp_adapter {TYPE_1__ pool; TYPE_2__* gs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct zfcp_fc_req* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct zfcp_fc_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_fc_req*,int /*<<< orphan*/ ,int) ; 
 int zfcp_fc_ns_gid_pn_request (struct zfcp_port*,struct zfcp_fc_req*) ; 
 int zfcp_fc_wka_port_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_fc_ns_gid_pn(struct zfcp_port *port)
{
	int ret;
	struct zfcp_fc_req *fc_req;
	struct zfcp_adapter *adapter = port->adapter;

	fc_req = mempool_alloc(adapter->pool.gid_pn, GFP_ATOMIC);
	if (!fc_req)
		return -ENOMEM;

	memset(fc_req, 0, sizeof(*fc_req));

	ret = zfcp_fc_wka_port_get(&adapter->gs->ds);
	if (ret)
		goto out;

	ret = zfcp_fc_ns_gid_pn_request(port, fc_req);

	zfcp_fc_wka_port_put(&adapter->gs->ds);
out:
	mempool_free(fc_req, adapter->pool.gid_pn);
	return ret;
}