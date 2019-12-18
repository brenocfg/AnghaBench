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
typedef  int u32 ;
typedef  void* u16 ;
struct fc_seq {scalar_t__ id; } ;
struct fc_frame_header {scalar_t__ fh_seq_id; int /*<<< orphan*/  fh_rx_id; int /*<<< orphan*/  fh_ox_id; int /*<<< orphan*/  fh_f_ctl; } ;
struct fc_frame {int dummy; } ;
struct fc_exch_mgr {int dummy; } ;
struct fc_exch {scalar_t__ rxid; struct fc_seq seq; } ;

/* Variables and functions */
 int FC_FC_EX_CTX ; 
 int FC_FC_SEQ_CTX ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct fc_exch* fc_exch_find (struct fc_exch_mgr*,void*) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fc_seq *fc_seq_lookup_orig(struct fc_exch_mgr *mp,
					 struct fc_frame *fp)
{
	struct fc_frame_header *fh = fc_frame_header_get(fp);
	struct fc_exch *ep;
	struct fc_seq *sp = NULL;
	u32 f_ctl;
	u16 xid;

	f_ctl = ntoh24(fh->fh_f_ctl);
	WARN_ON((f_ctl & FC_FC_SEQ_CTX) != FC_FC_SEQ_CTX);
	xid = ntohs((f_ctl & FC_FC_EX_CTX) ? fh->fh_ox_id : fh->fh_rx_id);
	ep = fc_exch_find(mp, xid);
	if (!ep)
		return NULL;
	if (ep->seq.id == fh->fh_seq_id) {
		/*
		 * Save the RX_ID if we didn't previously know it.
		 */
		sp = &ep->seq;
		if ((f_ctl & FC_FC_EX_CTX) != 0 &&
		    ep->rxid == FC_XID_UNKNOWN) {
			ep->rxid = ntohs(fh->fh_rx_id);
		}
	}
	fc_exch_release(ep);
	return sp;
}