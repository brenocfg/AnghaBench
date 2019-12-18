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
struct ath9k_tx_queue_info {int dummy; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;
typedef  int /*<<< orphan*/  qi ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_HTC_INIT_TXQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH9K_TX_QUEUE_CAB ; 
 int ath9k_hw_setuptxqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  memset (struct ath9k_tx_queue_info*,int /*<<< orphan*/ ,int) ; 

int ath9k_htc_cabq_setup(struct ath9k_htc_priv *priv)
{
	struct ath9k_tx_queue_info qi;

	memset(&qi, 0, sizeof(qi));
	ATH9K_HTC_INIT_TXQ(0);

	return ath9k_hw_setuptxqueue(priv->ah, ATH9K_TX_QUEUE_CAB, &qi);
}