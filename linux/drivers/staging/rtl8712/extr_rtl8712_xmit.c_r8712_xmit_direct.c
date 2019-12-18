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
struct xmit_frame {int /*<<< orphan*/ * pkt; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  dump_xframe (struct _adapter*,struct xmit_frame*) ; 
 int r8712_xmitframe_coalesce (struct _adapter*,int /*<<< orphan*/ *,struct xmit_frame*) ; 

void r8712_xmit_direct(struct _adapter *padapter, struct xmit_frame *pxmitframe)
{
	int res;

	res = r8712_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	pxmitframe->pkt = NULL;
	if (res == _SUCCESS)
		dump_xframe(padapter, pxmitframe);
}