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
struct mlme_ext_info {scalar_t__ HT_enable; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_11B ; 
 int /*<<< orphan*/  WIRELESS_11BG ; 
 int /*<<< orphan*/  WIRELESS_11G ; 
 int /*<<< orphan*/  WIRELESS_11_24N ; 
 scalar_t__ cckrates_included (unsigned char*,int) ; 
 scalar_t__ cckratesonly_included (unsigned char*,int) ; 

u8 judge_network_type(struct adapter *padapter, unsigned char *rate, int ratelen)
{
	u8 network_type = 0;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (pmlmeinfo->HT_enable)
		network_type = WIRELESS_11_24N;

	if (cckratesonly_included(rate, ratelen))
		network_type |= WIRELESS_11B;
	else if (cckrates_included(rate, ratelen))
		network_type |= WIRELESS_11BG;
	else
		network_type |= WIRELESS_11G;

	return network_type;
}