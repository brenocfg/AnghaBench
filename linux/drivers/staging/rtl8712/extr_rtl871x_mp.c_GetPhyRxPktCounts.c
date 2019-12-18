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
 int RPTMaxCount ; 
 int /*<<< orphan*/  RXERR_RPT ; 
 int r8712_read32 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 GetPhyRxPktCounts(struct _adapter *pAdapter, u32 selbit)
{
	/*selection*/
	u32 phyrx_set = 0;
	u32 SelectBit;

	SelectBit = selbit << 28;
	phyrx_set |= (SelectBit & 0xF0000000);
	r8712_write32(pAdapter, RXERR_RPT, phyrx_set);
	/*Read packet count*/
	return r8712_read32(pAdapter, RXERR_RPT) & RPTMaxCount;
}