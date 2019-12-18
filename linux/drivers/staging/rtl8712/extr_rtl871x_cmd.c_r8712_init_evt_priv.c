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
struct evt_priv {scalar_t__ evt_done_cnt; scalar_t__ evt_allocated_buf; scalar_t__ evt_buf; scalar_t__ event_seq; } ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_EVTSZ ; 
 scalar_t__ kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

int r8712_init_evt_priv(struct evt_priv *pevtpriv)
{
	/* allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf */
	pevtpriv->event_seq = 0;
	pevtpriv->evt_allocated_buf = kmalloc(MAX_EVTSZ + 4, GFP_ATOMIC);

	if (!pevtpriv->evt_allocated_buf)
		return -ENOMEM;
	pevtpriv->evt_buf = pevtpriv->evt_allocated_buf  +  4 -
			    ((addr_t)(pevtpriv->evt_allocated_buf) & 3);
	pevtpriv->evt_done_cnt = 0;
	return 0;
}