#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u64 ;
typedef  void* u32 ;
struct TYPE_11__ {int /*<<< orphan*/  rdp; void** ossp; int /*<<< orphan*/  irh; int /*<<< orphan*/  ih2; } ;
struct TYPE_10__ {int /*<<< orphan*/  rdp; void** ossp; int /*<<< orphan*/  irh; int /*<<< orphan*/  pki_ih3; int /*<<< orphan*/  ih3; } ;
struct TYPE_12__ {TYPE_5__ cmd2; TYPE_4__ cmd3; } ;
struct octeon_soft_command {size_t iq_no; scalar_t__ rdatasize; TYPE_6__ cmd; scalar_t__ datasize; } ;
struct octeon_instr_rdp {scalar_t__ rlen; int /*<<< orphan*/  pcie_port; } ;
struct octeon_instr_pki_ih3 {int w; int raw; int utag; int utt; int pm; int sl; int /*<<< orphan*/  qpg; void* tagtype; void* tag; int /*<<< orphan*/  uqpg; } ;
struct octeon_instr_irh {int opcode; int subcode; int rflag; void* ossp; } ;
struct octeon_instr_ih3 {int /*<<< orphan*/  fsz; scalar_t__ dlengsz; int /*<<< orphan*/  pkind; } ;
struct octeon_instr_ih2 {int raw; int rs; int /*<<< orphan*/  fsz; scalar_t__ dlengsz; int /*<<< orphan*/  grp; void* tag; void* tagtype; } ;
struct octeon_device {int /*<<< orphan*/  pcie_port; TYPE_3__** instr_queue; } ;
struct octeon_config {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctrl_qpg; int /*<<< orphan*/  use_qpg; int /*<<< orphan*/  pkind; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_2__ txpciq; } ;

/* Variables and functions */
 void* ATOMIC_TAG ; 
 int /*<<< orphan*/  CFG_GET_CTRL_Q_GRP (struct octeon_config*) ; 
 void* LIO_CONTROL ; 
 int /*<<< orphan*/  LIO_PCICMD_O2 ; 
 int /*<<< orphan*/  LIO_PCICMD_O3 ; 
 int /*<<< orphan*/  LIO_SOFTCMDRESP_IH2 ; 
 int /*<<< orphan*/  LIO_SOFTCMDRESP_IH3 ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct octeon_config* octeon_get_conf (struct octeon_device*) ; 

void
octeon_prepare_soft_command(struct octeon_device *oct,
			    struct octeon_soft_command *sc,
			    u8 opcode,
			    u8 subcode,
			    u32 irh_ossp,
			    u64 ossp0,
			    u64 ossp1)
{
	struct octeon_config *oct_cfg;
	struct octeon_instr_ih2 *ih2;
	struct octeon_instr_ih3 *ih3;
	struct octeon_instr_pki_ih3 *pki_ih3;
	struct octeon_instr_irh *irh;
	struct octeon_instr_rdp *rdp;

	WARN_ON(opcode > 15);
	WARN_ON(subcode > 127);

	oct_cfg = octeon_get_conf(oct);

	if (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) {
		ih3 = (struct octeon_instr_ih3 *)&sc->cmd.cmd3.ih3;

		ih3->pkind = oct->instr_queue[sc->iq_no]->txpciq.s.pkind;

		pki_ih3 = (struct octeon_instr_pki_ih3 *)&sc->cmd.cmd3.pki_ih3;

		pki_ih3->w           = 1;
		pki_ih3->raw         = 1;
		pki_ih3->utag        = 1;
		pki_ih3->uqpg        =
			oct->instr_queue[sc->iq_no]->txpciq.s.use_qpg;
		pki_ih3->utt         = 1;
		pki_ih3->tag     = LIO_CONTROL;
		pki_ih3->tagtype = ATOMIC_TAG;
		pki_ih3->qpg         =
			oct->instr_queue[sc->iq_no]->txpciq.s.ctrl_qpg;

		pki_ih3->pm          = 0x7;
		pki_ih3->sl          = 8;

		if (sc->datasize)
			ih3->dlengsz = sc->datasize;

		irh            = (struct octeon_instr_irh *)&sc->cmd.cmd3.irh;
		irh->opcode    = opcode;
		irh->subcode   = subcode;

		/* opcode/subcode specific parameters (ossp) */
		irh->ossp       = irh_ossp;
		sc->cmd.cmd3.ossp[0] = ossp0;
		sc->cmd.cmd3.ossp[1] = ossp1;

		if (sc->rdatasize) {
			rdp = (struct octeon_instr_rdp *)&sc->cmd.cmd3.rdp;
			rdp->pcie_port = oct->pcie_port;
			rdp->rlen      = sc->rdatasize;

			irh->rflag =  1;
			/*PKI IH3*/
			/* pki_ih3 irh+ossp[0]+ossp[1]+rdp+rptr = 48 bytes */
			ih3->fsz    = LIO_SOFTCMDRESP_IH3;
		} else {
			irh->rflag =  0;
			/*PKI IH3*/
			/* pki_h3 + irh + ossp[0] + ossp[1] = 32 bytes */
			ih3->fsz    = LIO_PCICMD_O3;
		}

	} else {
		ih2          = (struct octeon_instr_ih2 *)&sc->cmd.cmd2.ih2;
		ih2->tagtype = ATOMIC_TAG;
		ih2->tag     = LIO_CONTROL;
		ih2->raw     = 1;
		ih2->grp     = CFG_GET_CTRL_Q_GRP(oct_cfg);

		if (sc->datasize) {
			ih2->dlengsz = sc->datasize;
			ih2->rs = 1;
		}

		irh            = (struct octeon_instr_irh *)&sc->cmd.cmd2.irh;
		irh->opcode    = opcode;
		irh->subcode   = subcode;

		/* opcode/subcode specific parameters (ossp) */
		irh->ossp       = irh_ossp;
		sc->cmd.cmd2.ossp[0] = ossp0;
		sc->cmd.cmd2.ossp[1] = ossp1;

		if (sc->rdatasize) {
			rdp = (struct octeon_instr_rdp *)&sc->cmd.cmd2.rdp;
			rdp->pcie_port = oct->pcie_port;
			rdp->rlen      = sc->rdatasize;

			irh->rflag =  1;
			/* irh+ossp[0]+ossp[1]+rdp+rptr = 40 bytes */
			ih2->fsz   = LIO_SOFTCMDRESP_IH2;
		} else {
			irh->rflag =  0;
			/* irh + ossp[0] + ossp[1] = 24 bytes */
			ih2->fsz   = LIO_PCICMD_O2;
		}
	}
}