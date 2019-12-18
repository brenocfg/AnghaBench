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
struct fc_seq {int dummy; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {int f_ctl; int /*<<< orphan*/  lp; int /*<<< orphan*/  sid; int /*<<< orphan*/  did; } ;
typedef  enum fc_rctl { ____Placeholder_fc_rctl } fc_rctl ;
typedef  enum fc_fh_type { ____Placeholder_fc_fh_type } fc_fh_type ;

/* Variables and functions */
 int FC_FC_END_SEQ ; 
 int FC_FC_LAST_SEQ ; 
 int FC_FC_SEQ_INIT ; 
 int /*<<< orphan*/  fc_fill_fc_hdr (struct fc_frame*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  fc_seq_send_locked (int /*<<< orphan*/ ,struct fc_seq*,struct fc_frame*) ; 

__attribute__((used)) static void fc_seq_send_last(struct fc_seq *sp, struct fc_frame *fp,
			     enum fc_rctl rctl, enum fc_fh_type fh_type)
{
	u32 f_ctl;
	struct fc_exch *ep = fc_seq_exch(sp);

	f_ctl = FC_FC_LAST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT;
	f_ctl |= ep->f_ctl;
	fc_fill_fc_hdr(fp, rctl, ep->did, ep->sid, fh_type, f_ctl, 0);
	fc_seq_send_locked(ep->lp, sp, fp);
}