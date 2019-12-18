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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tx_desc {int /*<<< orphan*/  txdw4; int /*<<< orphan*/  txdw2; int /*<<< orphan*/  txdw3; int /*<<< orphan*/  txdw1; int /*<<< orphan*/  txdw0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FSG ; 
 int LSG ; 
 int NAVUSEHDR ; 
 int OFFSET_SHT ; 
 int OFFSET_SZ ; 
 int OWN ; 
 int QSEL_SHT ; 
 int QSLT_MGNT ; 
 int TXDESC_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8188eu_cal_txdesc_chksum (struct tx_desc*) ; 

void rtl8188e_fill_fake_txdesc(struct adapter *adapt, u8 *desc, u32 BufferLen, u8  ispspoll, u8  is_btqosnull)
{
	struct tx_desc *ptxdesc;

	/*  Clear all status */
	ptxdesc = (struct tx_desc *)desc;
	memset(desc, 0, TXDESC_SIZE);

	/* offset 0 */
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG); /* own, bFirstSeg, bLastSeg; */

	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE+OFFSET_SZ)<<OFFSET_SHT)&0x00ff0000); /* 32 bytes for TX Desc */

	ptxdesc->txdw0 |= cpu_to_le32(BufferLen&0x0000ffff); /*  Buffer size + command header */

	/* offset 4 */
	ptxdesc->txdw1 |= cpu_to_le32((QSLT_MGNT<<QSEL_SHT)&0x00001f00); /*  Fixed queue of Mgnt queue */

	/* Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error vlaue by Hw. */
	if (ispspoll) {
		ptxdesc->txdw1 |= cpu_to_le32(NAVUSEHDR);
	} else {
		ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); /*  Hw set sequence number */
		ptxdesc->txdw3 |= cpu_to_le32((8 << 28)); /* set bit3 to 1. Suugested by TimChen. 2009.12.29. */
	}

	if (is_btqosnull)
		ptxdesc->txdw2 |= cpu_to_le32(BIT(23)); /*  BT NULL */

	/* offset 16 */
	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));/* driver uses rate */

	/*  USB interface drop packet if the checksum of descriptor isn't correct. */
	/*  Using this checksum can let hardware recovery from packet bulk out error (e.g. Cancel URC, Bulk out error.). */
	rtl8188eu_cal_txdesc_chksum(ptxdesc);
}