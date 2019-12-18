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
typedef  int /*<<< orphan*/  u32 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACvSetCurrAC0DescAddrEx (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSetCurrTx0DescAddrEx (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int TYPE_AC0DMA ; 
 int TYPE_TXDMA0 ; 

void MACvSetCurrTXDescAddr(int iTxType, struct vnt_private *priv,
			   u32 curr_desc_addr)
{
	if (iTxType == TYPE_AC0DMA)
		MACvSetCurrAC0DescAddrEx(priv, curr_desc_addr);
	else if (iTxType == TYPE_TXDMA0)
		MACvSetCurrTx0DescAddrEx(priv, curr_desc_addr);
}