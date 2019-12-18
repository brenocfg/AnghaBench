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
struct ath10k_htc_lookahead_report {int pre_valid; int post_valid; int /*<<< orphan*/  lookahead; } ;
struct ath10k_htc {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ath10k_htc_process_lookahead(struct ath10k_htc *htc,
			     const struct ath10k_htc_lookahead_report *report,
			     int len,
			     enum ath10k_htc_ep_id eid,
			     void *next_lookaheads,
			     int *next_lookaheads_len)
{
	struct ath10k *ar = htc->ar;

	/* Invalid lookahead flags are actually transmitted by
	 * the target in the HTC control message.
	 * Since this will happen at every boot we silently ignore
	 * the lookahead in this case
	 */
	if (report->pre_valid != ((~report->post_valid) & 0xFF))
		return 0;

	if (next_lookaheads && next_lookaheads_len) {
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "htc rx lookahead found pre_valid 0x%x post_valid 0x%x\n",
			   report->pre_valid, report->post_valid);

		/* look ahead bytes are valid, copy them over */
		memcpy((u8 *)next_lookaheads, report->lookahead, 4);

		*next_lookaheads_len = 1;
	}

	return 0;
}