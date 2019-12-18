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
struct nvme_fc_remote_port {struct fcloop_rport* private; } ;
struct nvme_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct fcloop_rport {TYPE_2__* lport; struct fcloop_nport* nport; int /*<<< orphan*/ * targetport; struct nvme_fc_remote_port* remoteport; } ;
struct fcloop_nport {struct fcloop_rport* rport; TYPE_2__* lport; TYPE_1__* tport; int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pinfo ;
struct TYPE_4__ {int /*<<< orphan*/  localport; } ;
struct TYPE_3__ {TYPE_2__* lport; struct nvme_fc_remote_port* remoteport; int /*<<< orphan*/ * targetport; } ;

/* Variables and functions */
 int EIO ; 
 struct fcloop_nport* fcloop_alloc_nport (char const*,size_t,int) ; 
 int /*<<< orphan*/  fcloop_nport_put (struct fcloop_nport*) ; 
 int /*<<< orphan*/  memset (struct nvme_fc_port_info*,int /*<<< orphan*/ ,int) ; 
 int nvme_fc_register_remoteport (int /*<<< orphan*/ ,struct nvme_fc_port_info*,struct nvme_fc_remote_port**) ; 

__attribute__((used)) static ssize_t
fcloop_create_remote_port(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct nvme_fc_remote_port *remoteport;
	struct fcloop_nport *nport;
	struct fcloop_rport *rport;
	struct nvme_fc_port_info pinfo;
	int ret;

	nport = fcloop_alloc_nport(buf, count, true);
	if (!nport)
		return -EIO;

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.node_name = nport->node_name;
	pinfo.port_name = nport->port_name;
	pinfo.port_role = nport->port_role;
	pinfo.port_id = nport->port_id;

	ret = nvme_fc_register_remoteport(nport->lport->localport,
						&pinfo, &remoteport);
	if (ret || !remoteport) {
		fcloop_nport_put(nport);
		return ret;
	}

	/* success */
	rport = remoteport->private;
	rport->remoteport = remoteport;
	rport->targetport = (nport->tport) ?  nport->tport->targetport : NULL;
	if (nport->tport) {
		nport->tport->remoteport = remoteport;
		nport->tport->lport = nport->lport;
	}
	rport->nport = nport;
	rport->lport = nport->lport;
	nport->rport = rport;

	return count;
}