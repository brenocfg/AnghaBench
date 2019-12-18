#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tsflag; int /*<<< orphan*/  tnl_csum; int /*<<< orphan*/  transport_csum; int /*<<< orphan*/  ip_csum; } ;
union octnic_packet_params {scalar_t__ u32; TYPE_6__ s; } ;
struct TYPE_11__ {int /*<<< orphan*/  gatherptrs; int /*<<< orphan*/  datasize; } ;
struct TYPE_14__ {size_t iq_no; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  tnl_csum; int /*<<< orphan*/  transport_csum; int /*<<< orphan*/  ip_csum; TYPE_4__ u; int /*<<< orphan*/  gather; } ;
union octnic_cmd_setup {TYPE_7__ s; } ;
struct TYPE_12__ {int /*<<< orphan*/  irh; int /*<<< orphan*/  ih2; } ;
union octeon_instr_64B {TYPE_5__ cmd2; } ;
typedef  scalar_t__ u32 ;
struct octeon_instr_irh {scalar_t__ ossp; int /*<<< orphan*/  subcode; int /*<<< orphan*/  opcode; } ;
struct octeon_instr_ih2 {int raw; int qos; int gather; int /*<<< orphan*/  dlengsz; scalar_t__ tag; int /*<<< orphan*/  grp; int /*<<< orphan*/  tagtype; int /*<<< orphan*/  fsz; } ;
struct octeon_device {TYPE_3__** instr_queue; } ;
struct TYPE_8__ {scalar_t__ port; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
struct TYPE_10__ {TYPE_2__ txpciq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_POW_GRP ; 
 scalar_t__ LIO_DATA (int) ; 
 int /*<<< orphan*/  LIO_PCICMD_O2 ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_NW_DATA ; 
 int /*<<< orphan*/  ORDERED_TAG ; 
 int /*<<< orphan*/  memset (union octeon_instr_64B*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
octnet_prepare_pci_cmd_o2(struct octeon_device *oct,
			  union octeon_instr_64B *cmd,
			  union octnic_cmd_setup *setup, u32 tag)
{
	struct octeon_instr_ih2 *ih2;
	struct octeon_instr_irh *irh;
	union octnic_packet_params packet_params;
	int port;

	memset(cmd, 0, sizeof(union octeon_instr_64B));

	ih2 = (struct octeon_instr_ih2 *)&cmd->cmd2.ih2;

	/* assume that rflag is cleared so therefore front data will only have
	 * irh and ossp[0], ossp[1] for a total of 32 bytes
	 */
	ih2->fsz = LIO_PCICMD_O2;

	ih2->tagtype = ORDERED_TAG;
	ih2->grp = DEFAULT_POW_GRP;

	port = (int)oct->instr_queue[setup->s.iq_no]->txpciq.s.port;

	if (tag)
		ih2->tag = tag;
	else
		ih2->tag = LIO_DATA(port);

	ih2->raw = 1;
	ih2->qos = (port & 3) + 4;	/* map qos based on interface */

	if (!setup->s.gather) {
		ih2->dlengsz = setup->s.u.datasize;
	} else {
		ih2->gather = 1;
		ih2->dlengsz = setup->s.u.gatherptrs;
	}

	irh = (struct octeon_instr_irh *)&cmd->cmd2.irh;

	irh->opcode = OPCODE_NIC;
	irh->subcode = OPCODE_NIC_NW_DATA;

	packet_params.u32 = 0;

	packet_params.s.ip_csum = setup->s.ip_csum;
	packet_params.s.transport_csum = setup->s.transport_csum;
	packet_params.s.tnl_csum = setup->s.tnl_csum;
	packet_params.s.tsflag = setup->s.timestamp;

	irh->ossp = packet_params.u32;
}