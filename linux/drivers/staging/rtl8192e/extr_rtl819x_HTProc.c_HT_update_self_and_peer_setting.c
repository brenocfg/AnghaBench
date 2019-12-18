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
struct TYPE_2__ {scalar_t__ bdHTInfoLen; scalar_t__ bdHTInfoBuf; } ;
struct rtllib_network {TYPE_1__ bssht; } ;
struct rtllib_device {struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int /*<<< orphan*/  CurrentOpMode; scalar_t__ bCurrentHTSupport; } ;
struct ht_info_ele {int /*<<< orphan*/  OptMode; } ;

/* Variables and functions */

void HT_update_self_and_peer_setting(struct rtllib_device *ieee,
				     struct rtllib_network *pNetwork)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	struct ht_info_ele *pPeerHTInfo =
		 (struct ht_info_ele *)pNetwork->bssht.bdHTInfoBuf;

	if (pHTInfo->bCurrentHTSupport) {
		if (pNetwork->bssht.bdHTInfoLen != 0)
			pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;
	}
}