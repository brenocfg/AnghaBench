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
typedef  int /*<<< orphan*/  u8 ;
struct pkt_attrib {int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GetAddr1Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetAddr2Ptr (int /*<<< orphan*/ *) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_mgntframe_attrib_addr(struct adapter *padapter, struct xmit_frame *pmgntframe)
{
	u8 *pframe;
	struct pkt_attrib	*pattrib = &pmgntframe->attrib;

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	memcpy(pattrib->ra, GetAddr1Ptr(pframe), ETH_ALEN);
	memcpy(pattrib->ta, GetAddr2Ptr(pframe), ETH_ALEN);
}