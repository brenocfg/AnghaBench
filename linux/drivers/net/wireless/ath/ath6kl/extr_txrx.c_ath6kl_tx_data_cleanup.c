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
struct ath6kl {int /*<<< orphan*/ * ac2ep_map; int /*<<< orphan*/  htc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DATA_PKT_TAG ; 
 int WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_htc_flush_txep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath6kl_tx_data_cleanup(struct ath6kl *ar)
{
	int i;

	/* flush all the data (non-control) streams */
	for (i = 0; i < WMM_NUM_AC; i++)
		ath6kl_htc_flush_txep(ar->htc_target, ar->ac2ep_map[i],
				      ATH6KL_DATA_PKT_TAG);
}