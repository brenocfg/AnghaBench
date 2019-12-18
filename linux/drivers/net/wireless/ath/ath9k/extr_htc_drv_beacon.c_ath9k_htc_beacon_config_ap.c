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
struct ath_hw {scalar_t__ imask; } ;
struct ath_beacon_config {int dummy; } ;
struct ath9k_htc_priv {struct ath_hw* ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_HTC_MAX_BCN_VIF ; 
 int /*<<< orphan*/  ath9k_cmn_beacon_config_ap (struct ath_hw*,struct ath_beacon_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_htc_beacon_init (struct ath9k_htc_priv*,struct ath_beacon_config*,int) ; 

__attribute__((used)) static void ath9k_htc_beacon_config_ap(struct ath9k_htc_priv *priv,
				       struct ath_beacon_config *conf)
{
	struct ath_hw *ah = priv->ah;
	ah->imask = 0;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH9K_HTC_MAX_BCN_VIF);
	ath9k_htc_beacon_init(priv, conf, false);
}