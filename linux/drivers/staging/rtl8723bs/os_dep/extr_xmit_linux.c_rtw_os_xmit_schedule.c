#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmit_comp; TYPE_1__ pending_xmitbuf_queue; } ;
struct adapter {TYPE_2__ xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void rtw_os_xmit_schedule(struct adapter *padapter)
{
	struct adapter *pri_adapter = padapter;

	if (!padapter)
		return;

	if (!list_empty(&padapter->xmitpriv.pending_xmitbuf_queue.queue))
		complete(&pri_adapter->xmitpriv.xmit_comp);
}