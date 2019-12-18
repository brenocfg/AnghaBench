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
struct recv_priv {int /*<<< orphan*/  pallocated_frame_buf; struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_free_uc_swdec_pending_queue (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_free_recv_priv (struct adapter*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void _rtw_free_recv_priv(struct recv_priv *precvpriv)
{
	struct adapter	*padapter = precvpriv->adapter;

	rtw_free_uc_swdec_pending_queue(padapter);

	vfree(precvpriv->pallocated_frame_buf);

	rtw_hal_free_recv_priv(padapter);
}