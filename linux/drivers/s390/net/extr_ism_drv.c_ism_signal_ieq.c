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
struct TYPE_4__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {void* info; void* event_code; void* trigger_irq; void* rgid; TYPE_2__ hdr; } ;
union ism_sig_ieq {TYPE_1__ request; } ;
typedef  void* u64 ;
typedef  void* u32 ;
struct smcd_dev {struct ism_dev* priv; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_SIGNAL_IEQ ; 
 int ism_cmd (struct ism_dev*,union ism_sig_ieq*) ; 
 int /*<<< orphan*/  memset (union ism_sig_ieq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_signal_ieq(struct smcd_dev *smcd, u64 rgid, u32 trigger_irq,
			  u32 event_code, u64 info)
{
	struct ism_dev *ism = smcd->priv;
	union ism_sig_ieq cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_SIGNAL_IEQ;
	cmd.request.hdr.len = sizeof(cmd.request);

	cmd.request.rgid = rgid;
	cmd.request.trigger_irq = trigger_irq;
	cmd.request.event_code = event_code;
	cmd.request.info = info;

	return ism_cmd(ism, &cmd);
}