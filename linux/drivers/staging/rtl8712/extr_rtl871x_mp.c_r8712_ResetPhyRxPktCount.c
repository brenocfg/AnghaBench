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
typedef  int u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int HT_MPDU_FAIL_BIT ; 
 int OFDM_PPDU_BIT ; 
 int /*<<< orphan*/  RXERR_RPT ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,int /*<<< orphan*/ ,int) ; 

void r8712_ResetPhyRxPktCount(struct _adapter *pAdapter)
{
	u32 i, phyrx_set = 0;

	for (i = OFDM_PPDU_BIT; i <= HT_MPDU_FAIL_BIT; i++) {
		phyrx_set = 0;
		phyrx_set |= (i << 28);		/*select*/
		phyrx_set |= 0x08000000;	/* set counter to zero*/
		r8712_write32(pAdapter, RXERR_RPT, phyrx_set);
	}
}