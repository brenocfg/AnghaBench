#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rvu_pfvf {int rx_chan_cnt; int tx_chan_cnt; void* minlen; void* maxlen; void* rx_chan_base; int /*<<< orphan*/  mac_addr; void* tx_chan_base; int /*<<< orphan*/  cgx_lmac; } ;
struct rvu {int /*<<< orphan*/  dev; int /*<<< orphan*/ * pf2cgxlmac_map; } ;

/* Variables and functions */
 int EINVAL ; 
 void* NIC_HW_MIN_FRS ; 
 void* NIX_CHAN_CGX_LMAC_CHX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NIX_CHAN_LBK_CHX (int /*<<< orphan*/ ,int) ; 
#define  NIX_INTF_TYPE_CGX 129 
#define  NIX_INTF_TYPE_LBK 128 
 int RVU_PFVF_FUNC_MASK ; 
 int /*<<< orphan*/  cgx_set_pkind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  is_pf_cgxmapped (struct rvu*,int) ; 
 int nix_update_bcast_mce_list (struct rvu*,int,int) ; 
 int /*<<< orphan*/  rvu_cgx_pdata (int /*<<< orphan*/ ,struct rvu*) ; 
 int /*<<< orphan*/  rvu_get_cgx_lmac_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rvu_get_pf (int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 
 int rvu_npc_get_pkind (struct rvu*,int) ; 
 int /*<<< orphan*/  rvu_npc_install_bcast_match_entry (struct rvu*,int,int,void*) ; 
 int /*<<< orphan*/  rvu_npc_install_promisc_entry (struct rvu*,int,int,void*,int) ; 
 int /*<<< orphan*/  rvu_npc_install_ucast_entry (struct rvu*,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_npc_set_pkind (struct rvu*,int,struct rvu_pfvf*) ; 

__attribute__((used)) static int nix_interface_init(struct rvu *rvu, u16 pcifunc, int type, int nixlf)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	u8 cgx_id, lmac_id;
	int pkind, pf, vf;
	int err;

	pf = rvu_get_pf(pcifunc);
	if (!is_pf_cgxmapped(rvu, pf) && type != NIX_INTF_TYPE_LBK)
		return 0;

	switch (type) {
	case NIX_INTF_TYPE_CGX:
		pfvf->cgx_lmac = rvu->pf2cgxlmac_map[pf];
		rvu_get_cgx_lmac_id(pfvf->cgx_lmac, &cgx_id, &lmac_id);

		pkind = rvu_npc_get_pkind(rvu, pf);
		if (pkind < 0) {
			dev_err(rvu->dev,
				"PF_Func 0x%x: Invalid pkind\n", pcifunc);
			return -EINVAL;
		}
		pfvf->rx_chan_base = NIX_CHAN_CGX_LMAC_CHX(cgx_id, lmac_id, 0);
		pfvf->tx_chan_base = pfvf->rx_chan_base;
		pfvf->rx_chan_cnt = 1;
		pfvf->tx_chan_cnt = 1;
		cgx_set_pkind(rvu_cgx_pdata(cgx_id, rvu), lmac_id, pkind);
		rvu_npc_set_pkind(rvu, pkind, pfvf);
		break;
	case NIX_INTF_TYPE_LBK:
		vf = (pcifunc & RVU_PFVF_FUNC_MASK) - 1;
		pfvf->rx_chan_base = NIX_CHAN_LBK_CHX(0, vf);
		pfvf->tx_chan_base = vf & 0x1 ? NIX_CHAN_LBK_CHX(0, vf - 1) :
						NIX_CHAN_LBK_CHX(0, vf + 1);
		pfvf->rx_chan_cnt = 1;
		pfvf->tx_chan_cnt = 1;
		rvu_npc_install_promisc_entry(rvu, pcifunc, nixlf,
					      pfvf->rx_chan_base, false);
		break;
	}

	/* Add a UCAST forwarding rule in MCAM with this NIXLF attached
	 * RVU PF/VF's MAC address.
	 */
	rvu_npc_install_ucast_entry(rvu, pcifunc, nixlf,
				    pfvf->rx_chan_base, pfvf->mac_addr);

	/* Add this PF_FUNC to bcast pkt replication list */
	err = nix_update_bcast_mce_list(rvu, pcifunc, true);
	if (err) {
		dev_err(rvu->dev,
			"Bcast list, failed to enable PF_FUNC 0x%x\n",
			pcifunc);
		return err;
	}

	rvu_npc_install_bcast_match_entry(rvu, pcifunc,
					  nixlf, pfvf->rx_chan_base);
	pfvf->maxlen = NIC_HW_MIN_FRS;
	pfvf->minlen = NIC_HW_MIN_FRS;

	return 0;
}