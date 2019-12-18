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
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_priv {int /*<<< orphan*/  tx_rate; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */

void update_mgnt_tx_rate(struct adapter *padapter, u8 rate)
{
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	pmlmeext->tx_rate = rate;
	/* DBG_871X("%s(): rate = %x\n", __func__, rate); */
}