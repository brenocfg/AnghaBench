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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
struct ath9k_tx_queue_info {int dummy; } ;
struct ath9k_htc_priv {int* hwq_map; struct ath_hw* ah; } ;
typedef  int /*<<< orphan*/  qi ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ATH9K_HTC_INIT_TXQ (int) ; 
 int /*<<< orphan*/  ATH9K_TX_QUEUE_DATA ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_releasetxqueue (struct ath_hw*,int) ; 
 int ath9k_hw_setuptxqueue (struct ath_hw*,int /*<<< orphan*/ ,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int) ; 
 int /*<<< orphan*/  memset (struct ath9k_tx_queue_info*,int /*<<< orphan*/ ,int) ; 

bool ath9k_htc_txq_setup(struct ath9k_htc_priv *priv, int subtype)
{
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_tx_queue_info qi;
	int qnum;

	memset(&qi, 0, sizeof(qi));
	ATH9K_HTC_INIT_TXQ(subtype);

	qnum = ath9k_hw_setuptxqueue(priv->ah, ATH9K_TX_QUEUE_DATA, &qi);
	if (qnum == -1)
		return false;

	if (qnum >= ARRAY_SIZE(priv->hwq_map)) {
		ath_err(common, "qnum %u out of range, max %zu!\n",
			qnum, ARRAY_SIZE(priv->hwq_map));
		ath9k_hw_releasetxqueue(ah, qnum);
		return false;
	}

	priv->hwq_map[subtype] = qnum;
	return true;
}