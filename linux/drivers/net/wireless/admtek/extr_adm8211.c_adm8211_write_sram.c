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
typedef  int u32 ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ADM8211_REV_BA ; 
 int ADM8211_WEPCTL_SEL_WEPTABLE ; 
 int ADM8211_WEPCTL_TABLE_WR ; 
 int /*<<< orphan*/  WEPCTL ; 
 int /*<<< orphan*/  WESK ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline void adm8211_write_sram(struct ieee80211_hw *dev,
				      u32 addr, u32 data)
{
	struct adm8211_priv *priv = dev->priv;

	ADM8211_CSR_WRITE(WEPCTL, addr | ADM8211_WEPCTL_TABLE_WR |
			  (priv->pdev->revision < ADM8211_REV_BA ?
			   0 : ADM8211_WEPCTL_SEL_WEPTABLE ));
	ADM8211_CSR_READ(WEPCTL);
	msleep(1);

	ADM8211_CSR_WRITE(WESK, data);
	ADM8211_CSR_READ(WESK);
	msleep(1);
}