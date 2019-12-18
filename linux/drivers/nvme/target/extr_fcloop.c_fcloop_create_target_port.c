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
struct nvmet_fc_target_port {struct fcloop_tport* private; } ;
struct nvmet_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct fcloop_tport {int /*<<< orphan*/  lport; struct fcloop_nport* nport; int /*<<< orphan*/ * remoteport; struct nvmet_fc_target_port* targetport; } ;
struct fcloop_nport {struct fcloop_tport* tport; int /*<<< orphan*/  lport; TYPE_1__* rport; int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct nvmet_fc_target_port* targetport; int /*<<< orphan*/ * remoteport; } ;

/* Variables and functions */
 int EIO ; 
 struct fcloop_nport* fcloop_alloc_nport (char const*,size_t,int) ; 
 int /*<<< orphan*/  fcloop_nport_put (struct fcloop_nport*) ; 
 int nvmet_fc_register_targetport (struct nvmet_fc_port_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvmet_fc_target_port**) ; 
 int /*<<< orphan*/  tgttemplate ; 

__attribute__((used)) static ssize_t
fcloop_create_target_port(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct nvmet_fc_target_port *targetport;
	struct fcloop_nport *nport;
	struct fcloop_tport *tport;
	struct nvmet_fc_port_info tinfo;
	int ret;

	nport = fcloop_alloc_nport(buf, count, false);
	if (!nport)
		return -EIO;

	tinfo.node_name = nport->node_name;
	tinfo.port_name = nport->port_name;
	tinfo.port_id = nport->port_id;

	ret = nvmet_fc_register_targetport(&tinfo, &tgttemplate, NULL,
						&targetport);
	if (ret) {
		fcloop_nport_put(nport);
		return ret;
	}

	/* success */
	tport = targetport->private;
	tport->targetport = targetport;
	tport->remoteport = (nport->rport) ?  nport->rport->remoteport : NULL;
	if (nport->rport)
		nport->rport->targetport = targetport;
	tport->nport = nport;
	tport->lport = nport->lport;
	nport->tport = tport;

	return count;
}