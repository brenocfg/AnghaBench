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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ADM8211_REV_BA ; 
 int /*<<< orphan*/  WEPCTL ; 
 int /*<<< orphan*/  adm8211_write_sram (struct ieee80211_hw*,unsigned int,int) ; 

__attribute__((used)) static void adm8211_write_sram_bytes(struct ieee80211_hw *dev,
				     unsigned int addr, u8 *buf,
				     unsigned int len)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg = ADM8211_CSR_READ(WEPCTL);
	unsigned int i;

	if (priv->pdev->revision < ADM8211_REV_BA) {
		for (i = 0; i < len; i += 2) {
			u16 val = buf[i] | (buf[i + 1] << 8);
			adm8211_write_sram(dev, addr + i / 2, val);
		}
	} else {
		for (i = 0; i < len; i += 4) {
			u32 val = (buf[i + 0] << 0 ) | (buf[i + 1] << 8 ) |
				  (buf[i + 2] << 16) | (buf[i + 3] << 24);
			adm8211_write_sram(dev, addr + i / 4, val);
		}
	}

	ADM8211_CSR_WRITE(WEPCTL, reg);
}