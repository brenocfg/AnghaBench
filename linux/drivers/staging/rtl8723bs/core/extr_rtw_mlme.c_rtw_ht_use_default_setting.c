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
struct registry_priv {int /*<<< orphan*/  beamform_cap; int /*<<< orphan*/  stbc_cap; int /*<<< orphan*/  ldpc_cap; int /*<<< orphan*/  short_gi; scalar_t__ wifi_spec; } ;
struct ht_priv {int bss_coexist; int sgi_40m; int sgi_20m; scalar_t__ beamform_cap; scalar_t__ stbc_cap; scalar_t__ ldpc_cap; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct adapter {struct registry_priv registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEAMFORMING_HT_BEAMFORMEE_ENABLE ; 
 int /*<<< orphan*/  BEAMFORMING_HT_BEAMFORMER_ENABLE ; 
 int /*<<< orphan*/  BIT0 ; 
 int /*<<< orphan*/  BIT1 ; 
 int /*<<< orphan*/  BIT4 ; 
 int /*<<< orphan*/  BIT5 ; 
 int /*<<< orphan*/  CLEAR_FLAGS (scalar_t__) ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  HAL_DEF_EXPLICIT_BEAMFORMEE ; 
 int /*<<< orphan*/  HAL_DEF_EXPLICIT_BEAMFORMER ; 
 int /*<<< orphan*/  HAL_DEF_RX_LDPC ; 
 int /*<<< orphan*/  HAL_DEF_RX_STBC ; 
 int /*<<< orphan*/  HAL_DEF_TX_LDPC ; 
 int /*<<< orphan*/  HAL_DEF_TX_STBC ; 
 int /*<<< orphan*/  LDPC_HT_ENABLE_RX ; 
 int /*<<< orphan*/  LDPC_HT_ENABLE_TX ; 
 int /*<<< orphan*/  SET_FLAG (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STBC_HT_ENABLE_RX ; 
 int /*<<< orphan*/  STBC_HT_ENABLE_TX ; 
 scalar_t__ TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtw_ht_use_default_setting(struct adapter *padapter)
{
	struct mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	struct ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	bool		bHwLDPCSupport = false, bHwSTBCSupport = false;
	bool		bHwSupportBeamformer = false, bHwSupportBeamformee = false;

	if (pregistrypriv->wifi_spec)
		phtpriv->bss_coexist = 1;
	else
		phtpriv->bss_coexist = 0;

	phtpriv->sgi_40m = TEST_FLAG(pregistrypriv->short_gi, BIT1) ? true : false;
	phtpriv->sgi_20m = TEST_FLAG(pregistrypriv->short_gi, BIT0) ? true : false;

	/*  LDPC support */
	rtw_hal_get_def_var(padapter, HAL_DEF_RX_LDPC, (u8 *)&bHwLDPCSupport);
	CLEAR_FLAGS(phtpriv->ldpc_cap);
	if (bHwLDPCSupport) {
		if (TEST_FLAG(pregistrypriv->ldpc_cap, BIT4))
			SET_FLAG(phtpriv->ldpc_cap, LDPC_HT_ENABLE_RX);
	}
	rtw_hal_get_def_var(padapter, HAL_DEF_TX_LDPC, (u8 *)&bHwLDPCSupport);
	if (bHwLDPCSupport) {
		if (TEST_FLAG(pregistrypriv->ldpc_cap, BIT5))
			SET_FLAG(phtpriv->ldpc_cap, LDPC_HT_ENABLE_TX);
	}
	if (phtpriv->ldpc_cap)
		DBG_871X("[HT] Support LDPC = 0x%02X\n", phtpriv->ldpc_cap);

	/*  STBC */
	rtw_hal_get_def_var(padapter, HAL_DEF_TX_STBC, (u8 *)&bHwSTBCSupport);
	CLEAR_FLAGS(phtpriv->stbc_cap);
	if (bHwSTBCSupport) {
		if (TEST_FLAG(pregistrypriv->stbc_cap, BIT5))
			SET_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX);
	}
	rtw_hal_get_def_var(padapter, HAL_DEF_RX_STBC, (u8 *)&bHwSTBCSupport);
	if (bHwSTBCSupport) {
		if (TEST_FLAG(pregistrypriv->stbc_cap, BIT4))
			SET_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_RX);
	}
	if (phtpriv->stbc_cap)
		DBG_871X("[HT] Support STBC = 0x%02X\n", phtpriv->stbc_cap);

	/*  Beamforming setting */
	rtw_hal_get_def_var(padapter, HAL_DEF_EXPLICIT_BEAMFORMER, (u8 *)&bHwSupportBeamformer);
	rtw_hal_get_def_var(padapter, HAL_DEF_EXPLICIT_BEAMFORMEE, (u8 *)&bHwSupportBeamformee);
	CLEAR_FLAGS(phtpriv->beamform_cap);
	if (TEST_FLAG(pregistrypriv->beamform_cap, BIT4) && bHwSupportBeamformer) {
		SET_FLAG(phtpriv->beamform_cap, BEAMFORMING_HT_BEAMFORMER_ENABLE);
		DBG_871X("[HT] Support Beamformer\n");
	}
	if (TEST_FLAG(pregistrypriv->beamform_cap, BIT5) && bHwSupportBeamformee) {
		SET_FLAG(phtpriv->beamform_cap, BEAMFORMING_HT_BEAMFORMEE_ENABLE);
		DBG_871X("[HT] Support Beamformee\n");
	}
}