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
typedef  scalar_t__ u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_MPDU_OK_BIT ; 
 scalar_t__ GetPhyRxPktCounts (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_MPDU_OK_BIT ; 
 int /*<<< orphan*/  OFDM_MPDU_OK_BIT ; 

u32 r8712_GetPhyRxPktReceived(struct _adapter *pAdapter)
{
	u32 OFDM_cnt = GetPhyRxPktCounts(pAdapter, OFDM_MPDU_OK_BIT);
	u32 CCK_cnt  = GetPhyRxPktCounts(pAdapter, CCK_MPDU_OK_BIT);
	u32 HT_cnt   = GetPhyRxPktCounts(pAdapter, HT_MPDU_OK_BIT);

	return OFDM_cnt + CCK_cnt + HT_cnt;
}