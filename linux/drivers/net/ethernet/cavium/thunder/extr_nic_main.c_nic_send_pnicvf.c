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
struct TYPE_2__ {int /*<<< orphan*/  nicvf; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ nicvf; } ;
struct nicpf {size_t* pqs_vf; int /*<<< orphan*/ * nicvf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_PNICVF_PTR ; 
 int /*<<< orphan*/  nic_send_msg_to_vf (struct nicpf*,int,union nic_mbx*) ; 

__attribute__((used)) static void nic_send_pnicvf(struct nicpf *nic, int sqs)
{
	union nic_mbx mbx = {};

	mbx.nicvf.msg = NIC_MBOX_MSG_PNICVF_PTR;
	mbx.nicvf.nicvf = nic->nicvf[nic->pqs_vf[sqs]];
	nic_send_msg_to_vf(nic, sqs, &mbx);
}