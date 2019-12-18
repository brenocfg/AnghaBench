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
struct TYPE_2__ {scalar_t__ nicvf; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ nicvf; } ;
typedef  scalar_t__ u64 ;
struct nicvf {int /*<<< orphan*/  sqs_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_NICVF_PTR ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_send_vf_struct(struct nicvf *nic)
{
	union nic_mbx mbx = {};

	mbx.nicvf.msg = NIC_MBOX_MSG_NICVF_PTR;
	mbx.nicvf.sqs_mode = nic->sqs_mode;
	mbx.nicvf.nicvf = (u64)nic;
	nicvf_send_msg_to_pf(nic, &mbx);
}