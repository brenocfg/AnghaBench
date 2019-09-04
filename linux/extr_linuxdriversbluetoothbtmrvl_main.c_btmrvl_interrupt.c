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
struct TYPE_3__ {int /*<<< orphan*/  wait_q; } ;
struct btmrvl_private {TYPE_1__ main_thread; TYPE_2__* adapter; } ;
struct TYPE_4__ {scalar_t__ hs_state; int /*<<< orphan*/  int_count; scalar_t__ wakeup_tries; int /*<<< orphan*/  ps_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 scalar_t__ HS_ACTIVATED ; 
 scalar_t__ HS_DEACTIVATED ; 
 int /*<<< orphan*/  PS_AWAKE ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void btmrvl_interrupt(struct btmrvl_private *priv)
{
	priv->adapter->ps_state = PS_AWAKE;

	priv->adapter->wakeup_tries = 0;

	priv->adapter->int_count++;

	if (priv->adapter->hs_state == HS_ACTIVATED) {
		BT_DBG("BT: HS DEACTIVATED in ISR!");
		priv->adapter->hs_state = HS_DEACTIVATED;
	}

	wake_up_interruptible(&priv->main_thread.wait_q);
}