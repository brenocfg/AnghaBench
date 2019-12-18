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
struct mlme_priv {int /*<<< orphan*/  free_bss_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_free_mlme_priv_ie_data (struct mlme_priv*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rtw_free_mlme_priv(struct mlme_priv *pmlmepriv)
{
	if (pmlmepriv) {
		rtw_free_mlme_priv_ie_data(pmlmepriv);
		vfree(pmlmepriv->free_bss_buf);
	}
}