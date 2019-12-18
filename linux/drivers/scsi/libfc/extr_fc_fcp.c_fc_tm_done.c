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
struct fc_seq {int dummy; } ;
struct fc_frame_header {scalar_t__ fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int /*<<< orphan*/ * seq_ptr; int /*<<< orphan*/  wait_for_comp; } ;

/* Variables and functions */
 scalar_t__ FC_TYPE_BLS ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_exch_done (struct fc_seq*) ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_resp (struct fc_fcp_pkt*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 

__attribute__((used)) static void fc_tm_done(struct fc_seq *seq, struct fc_frame *fp, void *arg)
{
	struct fc_fcp_pkt *fsp = arg;
	struct fc_frame_header *fh;

	if (IS_ERR(fp)) {
		/*
		 * If there is an error just let it timeout or wait
		 * for TMF to be aborted if it timedout.
		 *
		 * scsi-eh will escalate for when either happens.
		 */
		return;
	}

	if (fc_fcp_lock_pkt(fsp))
		goto out;

	/*
	 * raced with eh timeout handler.
	 */
	if (!fsp->seq_ptr || !fsp->wait_for_comp)
		goto out_unlock;

	fh = fc_frame_header_get(fp);
	if (fh->fh_type != FC_TYPE_BLS)
		fc_fcp_resp(fsp, fp);
	fsp->seq_ptr = NULL;
	fc_exch_done(seq);
out_unlock:
	fc_fcp_unlock_pkt(fsp);
out:
	fc_frame_free(fp);
}