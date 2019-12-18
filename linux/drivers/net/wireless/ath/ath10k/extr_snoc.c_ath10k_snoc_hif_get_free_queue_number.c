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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath10k_snoc {TYPE_1__* pipe_info; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ce_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ath10k_ce_num_free_src_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 

__attribute__((used)) static u16 ath10k_snoc_hif_get_free_queue_number(struct ath10k *ar, u8 pipe)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "hif get free queue number\n");

	return ath10k_ce_num_free_src_entries(ar_snoc->pipe_info[pipe].ce_hdl);
}