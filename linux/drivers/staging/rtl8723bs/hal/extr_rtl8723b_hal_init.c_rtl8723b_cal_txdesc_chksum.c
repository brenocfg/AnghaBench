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
typedef  int u16 ;
struct tx_desc {int /*<<< orphan*/  txdw7; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8723b_cal_txdesc_chksum(struct tx_desc *ptxdesc)
{
	u16 *usPtr = (u16 *)ptxdesc;
	u32 count;
	u32 index;
	u16 checksum = 0;


	/*  Clear first */
	ptxdesc->txdw7 &= cpu_to_le32(0xffff0000);

	/*  checksume is always calculated by first 32 bytes, */
	/*  and it doesn't depend on TX DESC length. */
	/*  Thomas, Lucas@SD4, 20130515 */
	count = 16;

	for (index = 0; index < count; index++) {
		checksum |= le16_to_cpu(*(__le16 *)(usPtr + index));
	}

	ptxdesc->txdw7 |= cpu_to_le32(checksum & 0x0000ffff);
}