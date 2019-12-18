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
typedef  scalar_t__ u8 ;
struct fcp_txrdy {int /*<<< orphan*/  ft_burst_len; int /*<<< orphan*/  ft_data_ro; } ;
struct fc_seq {int /*<<< orphan*/  rec_data; } ;
struct fc_lport {scalar_t__ state; } ;
struct fc_frame_header {scalar_t__ fh_r_ctl; scalar_t__ fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int state; int /*<<< orphan*/  xfer_contig_end; int /*<<< orphan*/  xfer_len; struct fc_lport* lp; } ;

/* Variables and functions */
 int FCPHF_CRC_UNCHECKED ; 
 int /*<<< orphan*/  FC_FCP_DBG (struct fc_fcp_pkt*,char*,scalar_t__,...) ; 
 scalar_t__ FC_RCTL_DD_CMD_STATUS ; 
 scalar_t__ FC_RCTL_DD_DATA_DESC ; 
 scalar_t__ FC_RCTL_DD_SOL_DATA ; 
 int FC_SRB_ABORTED ; 
 int FC_SRB_ABORT_PENDING ; 
 scalar_t__ FC_TYPE_BLS ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fc_fcp_abts_resp (struct fc_fcp_pkt*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_fcp_error (struct fc_fcp_pkt*,struct fc_frame*) ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_recv_data (struct fc_fcp_pkt*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_fcp_resp (struct fc_fcp_pkt*,struct fc_frame*) ; 
 int fc_fcp_send_data (struct fc_fcp_pkt*,struct fc_seq*,size_t,size_t) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fcp_txrdy* fc_frame_payload_get (struct fc_frame*,int) ; 
 int fr_flags (struct fc_frame*) ; 
 int fr_len (struct fc_frame*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_fcp_recv(struct fc_seq *seq, struct fc_frame *fp, void *arg)
{
	struct fc_fcp_pkt *fsp = (struct fc_fcp_pkt *)arg;
	struct fc_lport *lport = fsp->lp;
	struct fc_frame_header *fh;
	struct fcp_txrdy *dd;
	u8 r_ctl;
	int rc = 0;

	if (IS_ERR(fp)) {
		fc_fcp_error(fsp, fp);
		return;
	}

	fh = fc_frame_header_get(fp);
	r_ctl = fh->fh_r_ctl;

	if (lport->state != LPORT_ST_READY) {
		FC_FCP_DBG(fsp, "lport state %d, ignoring r_ctl %x\n",
			   lport->state, r_ctl);
		goto out;
	}
	if (fc_fcp_lock_pkt(fsp))
		goto out;

	if (fh->fh_type == FC_TYPE_BLS) {
		fc_fcp_abts_resp(fsp, fp);
		goto unlock;
	}

	if (fsp->state & (FC_SRB_ABORTED | FC_SRB_ABORT_PENDING)) {
		FC_FCP_DBG(fsp, "command aborted, ignoring r_ctl %x\n", r_ctl);
		goto unlock;
	}

	if (r_ctl == FC_RCTL_DD_DATA_DESC) {
		/*
		 * received XFER RDY from the target
		 * need to send data to the target
		 */
		WARN_ON(fr_flags(fp) & FCPHF_CRC_UNCHECKED);
		dd = fc_frame_payload_get(fp, sizeof(*dd));
		WARN_ON(!dd);

		rc = fc_fcp_send_data(fsp, seq,
				      (size_t) ntohl(dd->ft_data_ro),
				      (size_t) ntohl(dd->ft_burst_len));
		if (!rc)
			seq->rec_data = fsp->xfer_len;
	} else if (r_ctl == FC_RCTL_DD_SOL_DATA) {
		/*
		 * received a DATA frame
		 * next we will copy the data to the system buffer
		 */
		WARN_ON(fr_len(fp) < sizeof(*fh));	/* len may be 0 */
		fc_fcp_recv_data(fsp, fp);
		seq->rec_data = fsp->xfer_contig_end;
	} else if (r_ctl == FC_RCTL_DD_CMD_STATUS) {
		WARN_ON(fr_flags(fp) & FCPHF_CRC_UNCHECKED);

		fc_fcp_resp(fsp, fp);
	} else {
		FC_FCP_DBG(fsp, "unexpected frame.  r_ctl %x\n", r_ctl);
	}
unlock:
	fc_fcp_unlock_pkt(fsp);
out:
	fc_frame_free(fp);
}