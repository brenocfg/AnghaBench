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
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_desc_checksum (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _rtl_tx_desc_checksum(__le32 *txdesc)
{
	__le16 *ptr = (__le16 *)txdesc;
	u16	checksum = 0;
	u32 index;

	/* Clear first */
	set_tx_desc_tx_desc_checksum(txdesc, 0);
	for (index = 0; index < 16; index++)
		checksum = checksum ^ le16_to_cpu(*(ptr + index));
	set_tx_desc_tx_desc_checksum(txdesc, checksum);
}