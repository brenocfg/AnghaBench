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
struct lbs_private {int /*<<< orphan*/  auto_deepsleep_timer; int /*<<< orphan*/  tx_lockup_timer; int /*<<< orphan*/  command_timer; int /*<<< orphan*/  event_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_free_cmd_buffer (struct lbs_private*) ; 

__attribute__((used)) static void lbs_free_adapter(struct lbs_private *priv)
{
	lbs_free_cmd_buffer(priv);
	kfifo_free(&priv->event_fifo);
	del_timer(&priv->command_timer);
	del_timer(&priv->tx_lockup_timer);
	del_timer(&priv->auto_deepsleep_timer);
}