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
struct recv_buf {scalar_t__ pskb; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 

void rtw_os_recvbuf_resource_free(struct adapter *padapter, struct recv_buf *precvbuf)
{
	if (precvbuf->pskb) {
		dev_kfree_skb_any(precvbuf->pskb);
	}
}