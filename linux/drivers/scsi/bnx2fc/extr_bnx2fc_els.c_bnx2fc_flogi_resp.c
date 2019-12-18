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
typedef  int /*<<< orphan*/  u8 ;
struct fcoe_ctlr {int /*<<< orphan*/  (* update_mac ) (struct fc_lport*,int /*<<< orphan*/ *) ;TYPE_1__* sel_fcf; } ;
struct fc_seq {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame_header {int /*<<< orphan*/ * fh_d_id; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {struct fc_lport* lp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * granted_mac; } ;
struct TYPE_3__ {scalar_t__ fc_map; } ;

/* Variables and functions */
 int BNX2FC_FCOE_MAC_METHOD_FCF_MAP ; 
 int BNX2FC_FCOE_MAC_METHOD_FCOE_SET_MAC ; 
 int BNX2FC_FCOE_MAC_METHOD_GRANGED_MAC ; 
 int /*<<< orphan*/  BNX2FC_HBA_DBG (struct fc_lport*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_fcoe_set_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_flogi_resp (struct fc_seq*,struct fc_frame*,struct fc_lport*) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 TYPE_2__* fr_cb (struct fc_frame*) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2fc_flogi_resp(struct fc_seq *seq, struct fc_frame *fp,
			      void *arg)
{
	struct fcoe_ctlr *fip = arg;
	struct fc_exch *exch = fc_seq_exch(seq);
	struct fc_lport *lport = exch->lp;

	struct fc_frame_header *fh;
	u8 *granted_mac;
	u8 fcoe_mac[6];
	u8 fc_map[3];
	int method;

	if (IS_ERR(fp))
		goto done;

	fh = fc_frame_header_get(fp);
	granted_mac = fr_cb(fp)->granted_mac;

	/*
	 * We set the source MAC for FCoE traffic based on the Granted MAC
	 * address from the switch.
	 *
	 * If granted_mac is non-zero, we use that.
	 * If the granted_mac is zeroed out, create the FCoE MAC based on
	 * the sel_fcf->fc_map and the d_id fo the FLOGI frame.
	 * If sel_fcf->fc_map is 0, then we use the default FCF-MAC plus the
	 * d_id of the FLOGI frame.
	 */
	if (!is_zero_ether_addr(granted_mac)) {
		ether_addr_copy(fcoe_mac, granted_mac);
		method = BNX2FC_FCOE_MAC_METHOD_GRANGED_MAC;
	} else if (fip->sel_fcf && fip->sel_fcf->fc_map != 0) {
		hton24(fc_map, fip->sel_fcf->fc_map);
		fcoe_mac[0] = fc_map[0];
		fcoe_mac[1] = fc_map[1];
		fcoe_mac[2] = fc_map[2];
		fcoe_mac[3] = fh->fh_d_id[0];
		fcoe_mac[4] = fh->fh_d_id[1];
		fcoe_mac[5] = fh->fh_d_id[2];
		method = BNX2FC_FCOE_MAC_METHOD_FCF_MAP;
	} else {
		fc_fcoe_set_mac(fcoe_mac, fh->fh_d_id);
		method = BNX2FC_FCOE_MAC_METHOD_FCOE_SET_MAC;
	}

	BNX2FC_HBA_DBG(lport, "fcoe_mac=%pM method=%d\n", fcoe_mac, method);
	fip->update_mac(lport, fcoe_mac);
done:
	fc_lport_flogi_resp(seq, fp, lport);
}