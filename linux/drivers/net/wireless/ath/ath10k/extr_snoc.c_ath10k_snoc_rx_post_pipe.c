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
struct ath10k_snoc_pipe {scalar_t__ buf_sz; struct ath10k_ce_pipe* ce_hdl; struct ath10k* hif_ce_state; } ;
struct ath10k_snoc {int /*<<< orphan*/  rx_post_retry; } ;
struct ath10k_ce_pipe {int /*<<< orphan*/  dest_ring; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATH10K_SNOC_RX_POST_RETRY_MS ; 
 int ENOSPC ; 
 int __ath10k_ce_rx_num_free_bufs (struct ath10k_ce_pipe*) ; 
 int __ath10k_snoc_rx_post_buf (struct ath10k_snoc_pipe*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_snoc_rx_post_pipe(struct ath10k_snoc_pipe *pipe)
{
	struct ath10k *ar = pipe->hif_ce_state;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	int ret, num;

	if (pipe->buf_sz == 0)
		return;

	if (!ce_pipe->dest_ring)
		return;

	spin_lock_bh(&ce->ce_lock);
	num = __ath10k_ce_rx_num_free_bufs(ce_pipe);
	spin_unlock_bh(&ce->ce_lock);
	while (num--) {
		ret = __ath10k_snoc_rx_post_buf(pipe);
		if (ret) {
			if (ret == -ENOSPC)
				break;
			ath10k_warn(ar, "failed to post rx buf: %d\n", ret);
			mod_timer(&ar_snoc->rx_post_retry, jiffies +
				  ATH10K_SNOC_RX_POST_RETRY_MS);
			break;
		}
	}
}