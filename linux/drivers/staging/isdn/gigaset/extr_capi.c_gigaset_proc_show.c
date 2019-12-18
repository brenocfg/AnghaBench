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
struct seq_file {struct capi_ctr* private; } ;
struct cardstate {int channels; int mode; int mstate; TYPE_1__* bcs; scalar_t__ cidmode; scalar_t__ isdn_up; scalar_t__ connected; scalar_t__ running; scalar_t__ onechannel; int /*<<< orphan*/ * fwver; scalar_t__ gotfwver; int /*<<< orphan*/  myid; int /*<<< orphan*/  dev; } ;
struct capi_ctr {int /*<<< orphan*/  name; struct cardstate* driverdata; } ;
struct TYPE_2__ {char* corrupted; char* trans_down; char* trans_up; char* chstate; int proto2; } ;

/* Variables and functions */
#define  L2_BITSYNC 140 
#define  L2_HDLC 139 
#define  L2_VOICE 138 
#define  MS_INIT 137 
#define  MS_LOCKED 136 
#define  MS_READY 135 
#define  MS_RECOVER 134 
#define  MS_SHUTDOWN 133 
#define  MS_UNINITIALIZED 132 
#define  M_CID 131 
#define  M_CONFIG 130 
#define  M_UNIMODEM 129 
#define  M_UNKNOWN 128 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int gigaset_proc_show(struct seq_file *m, void *v)
{
	struct capi_ctr *ctr = m->private;
	struct cardstate *cs = ctr->driverdata;
	char *s;
	int i;

	seq_printf(m, "%-16s %s\n", "name", ctr->name);
	seq_printf(m, "%-16s %s %s\n", "dev",
		   dev_driver_string(cs->dev), dev_name(cs->dev));
	seq_printf(m, "%-16s %d\n", "id", cs->myid);
	if (cs->gotfwver)
		seq_printf(m, "%-16s %d.%d.%d.%d\n", "firmware",
			   cs->fwver[0], cs->fwver[1], cs->fwver[2], cs->fwver[3]);
	seq_printf(m, "%-16s %d\n", "channels", cs->channels);
	seq_printf(m, "%-16s %s\n", "onechannel", cs->onechannel ? "yes" : "no");

	switch (cs->mode) {
	case M_UNKNOWN:
		s = "unknown";
		break;
	case M_CONFIG:
		s = "config";
		break;
	case M_UNIMODEM:
		s = "Unimodem";
		break;
	case M_CID:
		s = "CID";
		break;
	default:
		s = "??";
	}
	seq_printf(m, "%-16s %s\n", "mode", s);

	switch (cs->mstate) {
	case MS_UNINITIALIZED:
		s = "uninitialized";
		break;
	case MS_INIT:
		s = "init";
		break;
	case MS_LOCKED:
		s = "locked";
		break;
	case MS_SHUTDOWN:
		s = "shutdown";
		break;
	case MS_RECOVER:
		s = "recover";
		break;
	case MS_READY:
		s = "ready";
		break;
	default:
		s = "??";
	}
	seq_printf(m, "%-16s %s\n", "mstate", s);

	seq_printf(m, "%-16s %s\n", "running", cs->running ? "yes" : "no");
	seq_printf(m, "%-16s %s\n", "connected", cs->connected ? "yes" : "no");
	seq_printf(m, "%-16s %s\n", "isdn_up", cs->isdn_up ? "yes" : "no");
	seq_printf(m, "%-16s %s\n", "cidmode", cs->cidmode ? "yes" : "no");

	for (i = 0; i < cs->channels; i++) {
		seq_printf(m, "[%d]%-13s %d\n", i, "corrupted",
			   cs->bcs[i].corrupted);
		seq_printf(m, "[%d]%-13s %d\n", i, "trans_down",
			   cs->bcs[i].trans_down);
		seq_printf(m, "[%d]%-13s %d\n", i, "trans_up",
			   cs->bcs[i].trans_up);
		seq_printf(m, "[%d]%-13s %d\n", i, "chstate",
			   cs->bcs[i].chstate);
		switch (cs->bcs[i].proto2) {
		case L2_BITSYNC:
			s = "bitsync";
			break;
		case L2_HDLC:
			s = "HDLC";
			break;
		case L2_VOICE:
			s = "voice";
			break;
		default:
			s = "??";
		}
		seq_printf(m, "[%d]%-13s %s\n", i, "proto2", s);
	}
	return 0;
}