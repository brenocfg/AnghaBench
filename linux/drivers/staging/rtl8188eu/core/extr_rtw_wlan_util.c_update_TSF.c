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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_priv {int TSFValue; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void update_TSF(struct mlme_ext_priv *pmlmeext, u8 *pframe, uint len)
{
	u8 *pIE;
	__le32 *pbuf;

	pIE = pframe + sizeof(struct ieee80211_hdr_3addr);
	pbuf = (__le32 *)pIE;

	pmlmeext->TSFValue = le32_to_cpu(*(pbuf + 1));

	pmlmeext->TSFValue = pmlmeext->TSFValue << 32;

	pmlmeext->TSFValue |= le32_to_cpu(*pbuf);
}