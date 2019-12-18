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
typedef  int /*<<< orphan*/  u16 ;
struct pkt_attrib {scalar_t__ encrypt; int /*<<< orphan*/  icv_len; scalar_t__ bswenc; scalar_t__ pktlen; scalar_t__ iv_len; scalar_t__ hdrlen; } ;

/* Variables and functions */
 scalar_t__ SNAP_SIZE ; 
 scalar_t__ _TKIP_ ; 

u32 rtw_calculate_wlan_pkt_size_by_attribue(struct pkt_attrib *pattrib)
{
	u32 len = 0;

	len = pattrib->hdrlen + pattrib->iv_len; /*  WLAN Header and IV */
	len += SNAP_SIZE + sizeof(u16); /*  LLC */
	len += pattrib->pktlen;
	if (pattrib->encrypt == _TKIP_)
		len += 8; /*  MIC */
	len += ((pattrib->bswenc) ? pattrib->icv_len : 0); /*  ICV */

	return len;
}