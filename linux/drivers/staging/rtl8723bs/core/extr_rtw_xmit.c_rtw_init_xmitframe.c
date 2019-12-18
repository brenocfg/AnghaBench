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
struct xmit_frame {int pg_num; int agg_num; scalar_t__ ack_report; int /*<<< orphan*/  frame_tag; int /*<<< orphan*/  attrib; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * buf_addr; } ;
struct pkt_attrib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FRAMETAG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_init_xmitframe(struct xmit_frame *pxframe)
{
	if (pxframe) { /* default value setting */
		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;

		memset(&pxframe->attrib, 0, sizeof(struct pkt_attrib));
		/* pxframe->attrib.psta = NULL; */

		pxframe->frame_tag = DATA_FRAMETAG;

		pxframe->pg_num = 1;
		pxframe->agg_num = 1;
		pxframe->ack_report = 0;
	}
}