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
struct TYPE_8__ {int /*<<< orphan*/  gatherptrs; int /*<<< orphan*/  datasize; } ;
struct TYPE_14__ {size_t iq_no; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  tnl_csum; int /*<<< orphan*/  transport_csum; int /*<<< orphan*/  ip_csum; TYPE_1__ u; int /*<<< orphan*/  gather; } ;
union octnic_cmd_setup {TYPE_7__ s; } ;
struct TYPE_12__ {int /*<<< orphan*/  irh; int /*<<< orphan*/  pki_ih3; int /*<<< orphan*/  ih3; } ;
union octeon_instr_64B {TYPE_5__ cmd3; } ;
typedef  scalar_t__ u32 ;
struct octeon_instr_pki_ih3 {int w; int raw; int utag; int utt; int pm; int sl; int /*<<< orphan*/  qpg; int /*<<< orphan*/  tagtype; scalar_t__ tag; int /*<<< orphan*/  uqpg; } ;
struct octeon_instr_irh {scalar_t__ ossp; int /*<<< orphan*/  subcode; int /*<<< orphan*/  opcode; } ;
struct octeon_instr_ih3 {int gather; int /*<<< orphan*/  dlengsz; int /*<<< orphan*/  fsz; int /*<<< orphan*/  pkind; } ;
struct octeon_device {TYPE_4__** instr_queue; } ;
struct TYPE_9__ {int /*<<< orphan*/  qpg; scalar_t__ port; int /*<<< orphan*/  use_qpg; int /*<<< orphan*/  pkind; } ;
struct TYPE_10__ {TYPE_2__ s; } ;
struct TYPE_11__ {TYPE_3__ txpciq; } ;

/* Variables and functions */
 scalar_t__ LIO_DATA (int) ; 
 int /*<<< orphan*/  LIO_PCICMD_O3 ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_NW_DATA ; 
 int /*<<< orphan*/  ORDERED_TAG ; 
 int /*<<< orphan*/  memset (union octeon_instr_64B*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
octnet_prepare_pci_cmd_o3(struct octeon_device *oct,
			  union octeon_instr_64B *cmd,
			  union octnic_cmd_setup *setup, u32 tag)
{
	struct octeon_instr_irh *irh;
	struct octeon_instr_ih3     *ih3;
	struct octeon_instr_pki_ih3 *pki_ih3;
	union octnic_packet_params packet_params;
	int port;

	memset(cmd, 0, sizeof(union octeon_instr_64B));

	ih3 = (struct octeon_instr_ih3 *)&cmd->cmd3.ih3;
	pki_ih3 = (struct octeon_instr_pki_ih3 *)&cmd->cmd3.pki_ih3;

	/* assume that rflag is cleared so therefore front data will only have
	 * irh and ossp[1] and ossp[2] for a total of 24 bytes
	 */
	ih3->pkind       = oct->instr_queue[setup->s.iq_no]->txpciq.s.pkind;
	/*PKI IH*/
	ih3->fsz = LIO_PCICMD_O3;

	if (!setup->s.gather) {
		ih3->dlengsz = setup->s.u.datasize;
	} else {
		ih3->gather = 1;
		ih3->dlengsz = setup->s.u.gatherptrs;
	}

	pki_ih3->w       = 1;
	pki_ih3->raw     = 1;
	pki_ih3->utag    = 1;
	pki_ih3->utt     = 1;
	pki_ih3->uqpg    = oct->instr_queue[setup->s.iq_no]->txpciq.s.use_qpg;

	port = (int)oct->instr_queue[setup->s.iq_no]->txpciq.s.port;

	if (tag)
		pki_ih3->tag = tag;
	else
		pki_ih3->tag     = LIO_DATA(port);

	pki_ih3->tagtype = ORDERED_TAG;
	pki_ih3->qpg     = oct->instr_queue[setup->s.iq_no]->txpciq.s.qpg;
	pki_ih3->pm      = 0x7; /*0x7 - meant for Parse nothing, uninterpreted*/
	pki_ih3->sl      = 8;   /* sl will be sizeof(pki_ih3)*/

	irh = (struct octeon_instr_irh *)&cmd->cmd3.irh;

	irh->opcode = OPCODE_NIC;
	irh->subcode = OPCODE_NIC_NW_DATA;

	packet_params.u32 = 0;

	packet_params.s.ip_csum = setup->s.ip_csum;
	packet_params.s.transport_csum = setup->s.transport_csum;
	packet_params.s.tnl_csum = setup->s.tnl_csum;
	packet_params.s.tsflag = setup->s.timestamp;

	irh->ossp = packet_params.u32;
}