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
struct ieee80211_vif {int type; scalar_t__ addr; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_IDLE () ; 
 int /*<<< orphan*/  ADM8211_RESTORE () ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  PAR0 ; 
 int /*<<< orphan*/  PAR1 ; 
 int /*<<< orphan*/  adm8211_update_mode (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm8211_add_interface(struct ieee80211_hw *dev,
				 struct ieee80211_vif *vif)
{
	struct adm8211_priv *priv = dev->priv;
	if (priv->mode != NL80211_IFTYPE_MONITOR)
		return -EOPNOTSUPP;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		priv->mode = vif->type;
		break;
	default:
		return -EOPNOTSUPP;
	}

	ADM8211_IDLE();

	ADM8211_CSR_WRITE(PAR0, le32_to_cpu(*(__le32 *)vif->addr));
	ADM8211_CSR_WRITE(PAR1, le16_to_cpu(*(__le16 *)(vif->addr + 4)));

	adm8211_update_mode(dev);

	ADM8211_RESTORE();

	return 0;
}