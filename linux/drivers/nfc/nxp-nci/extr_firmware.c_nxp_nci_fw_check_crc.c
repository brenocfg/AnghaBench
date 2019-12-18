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
typedef  int u16 ;
struct sk_buff {size_t len; scalar_t__ data; } ;

/* Variables and functions */
 size_t NXP_NCI_FW_CRC_LEN ; 
 int get_unaligned_be16 (scalar_t__) ; 
 int nxp_nci_fw_crc (scalar_t__,size_t) ; 

__attribute__((used)) static u16 nxp_nci_fw_check_crc(struct sk_buff *skb)
{
	u16 crc, frame_crc;
	size_t len = skb->len - NXP_NCI_FW_CRC_LEN;

	crc = nxp_nci_fw_crc(skb->data, len);
	frame_crc = get_unaligned_be16(skb->data + len);

	return (crc ^ frame_crc);
}