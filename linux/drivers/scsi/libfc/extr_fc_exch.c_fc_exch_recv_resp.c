#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fc_seq {int dummy; } ;
struct fc_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  non_bls_resp; int /*<<< orphan*/  xid_not_found; } ;
struct fc_exch_mgr {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_seq* fc_seq_lookup_orig (struct fc_exch_mgr*,struct fc_frame*) ; 

__attribute__((used)) static void fc_exch_recv_resp(struct fc_exch_mgr *mp, struct fc_frame *fp)
{
	struct fc_seq *sp;

	sp = fc_seq_lookup_orig(mp, fp);	/* doesn't hold sequence */

	if (!sp)
		atomic_inc(&mp->stats.xid_not_found);
	else
		atomic_inc(&mp->stats.non_bls_resp);

	fc_frame_free(fp);
}