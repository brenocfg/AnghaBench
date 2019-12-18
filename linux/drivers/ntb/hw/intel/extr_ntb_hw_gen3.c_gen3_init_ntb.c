#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int topo; } ;
struct intel_ntb_dev {int db_count; int hwerr_flags; TYPE_3__* self_reg; scalar_t__ self_mmio; scalar_t__ db_valid_mask; TYPE_2__* reg; TYPE_1__ ntb; int /*<<< orphan*/ * xlat_reg; int /*<<< orphan*/ * peer_reg; scalar_t__ db_link_mask; int /*<<< orphan*/  spad_count; int /*<<< orphan*/  mw_count; } ;
struct TYPE_6__ {scalar_t__ db_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* db_iowrite ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BIT_ULL (int) ; 
 int EINVAL ; 
 int GEN3_DB_COUNT ; 
 scalar_t__ GEN3_DB_LINK_BIT ; 
 int /*<<< orphan*/  GEN3_SPAD_COUNT ; 
 scalar_t__ GEN3_SPCICMD_OFFSET ; 
 int NTB_HWERR_MSIX_VECTOR32_BAD ; 
#define  NTB_TOPO_B2B_DSD 129 
#define  NTB_TOPO_B2B_USD 128 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  XEON_MW_COUNT ; 
 int /*<<< orphan*/  gen3_b2b_reg ; 
 TYPE_3__ gen3_pri_reg ; 
 int /*<<< orphan*/  gen3_sec_xlat ; 
 int gen3_setup_b2b_mw (struct intel_ntb_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xeon_b2b_dsd_addr ; 
 int /*<<< orphan*/  xeon_b2b_usd_addr ; 

__attribute__((used)) static int gen3_init_ntb(struct intel_ntb_dev *ndev)
{
	int rc;


	ndev->mw_count = XEON_MW_COUNT;
	ndev->spad_count = GEN3_SPAD_COUNT;
	ndev->db_count = GEN3_DB_COUNT;
	ndev->db_link_mask = GEN3_DB_LINK_BIT;

	/* DB fixup for using 31 right now */
	if (ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD)
		ndev->db_link_mask |= BIT_ULL(31);

	switch (ndev->ntb.topo) {
	case NTB_TOPO_B2B_USD:
	case NTB_TOPO_B2B_DSD:
		ndev->self_reg = &gen3_pri_reg;
		ndev->peer_reg = &gen3_b2b_reg;
		ndev->xlat_reg = &gen3_sec_xlat;

		if (ndev->ntb.topo == NTB_TOPO_B2B_USD) {
			rc = gen3_setup_b2b_mw(ndev,
					      &xeon_b2b_dsd_addr,
					      &xeon_b2b_usd_addr);
		} else {
			rc = gen3_setup_b2b_mw(ndev,
					      &xeon_b2b_usd_addr,
					      &xeon_b2b_dsd_addr);
		}

		if (rc)
			return rc;

		/* Enable Bus Master and Memory Space on the secondary side */
		iowrite16(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER,
			  ndev->self_mmio + GEN3_SPCICMD_OFFSET);

		break;

	default:
		return -EINVAL;
	}

	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;

	ndev->reg->db_iowrite(ndev->db_valid_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

	return 0;
}