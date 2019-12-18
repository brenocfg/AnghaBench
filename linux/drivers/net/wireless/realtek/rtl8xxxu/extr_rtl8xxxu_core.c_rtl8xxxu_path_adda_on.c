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
typedef  int /*<<< orphan*/  u32 ;
struct rtl8xxxu_priv {int tx_paths; TYPE_1__* fops; } ;
struct TYPE_2__ {int /*<<< orphan*/  adda_2t_path_on_b; int /*<<< orphan*/  adda_2t_path_on_a; int /*<<< orphan*/  adda_1t_init; int /*<<< orphan*/  adda_1t_path_on; } ;

/* Variables and functions */
 int RTL8XXXU_ADDA_REGS ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void rtl8xxxu_path_adda_on(struct rtl8xxxu_priv *priv, const u32 *regs,
			   bool path_a_on)
{
	u32 path_on;
	int i;

	if (priv->tx_paths == 1) {
		path_on = priv->fops->adda_1t_path_on;
		rtl8xxxu_write32(priv, regs[0], priv->fops->adda_1t_init);
	} else {
		path_on = path_a_on ? priv->fops->adda_2t_path_on_a :
			priv->fops->adda_2t_path_on_b;

		rtl8xxxu_write32(priv, regs[0], path_on);
	}

	for (i = 1 ; i < RTL8XXXU_ADDA_REGS ; i++)
		rtl8xxxu_write32(priv, regs[i], path_on);
}