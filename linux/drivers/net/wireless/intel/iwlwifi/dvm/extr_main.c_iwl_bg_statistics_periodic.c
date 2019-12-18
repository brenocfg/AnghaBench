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
struct timer_list {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 struct iwl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_is_ready_rf (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_send_statistics_request (struct iwl_priv*,int /*<<< orphan*/ ,int) ; 
 struct iwl_priv* priv ; 
 int /*<<< orphan*/  statistics_periodic ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_bg_statistics_periodic(struct timer_list *t)
{
	struct iwl_priv *priv = from_timer(priv, t, statistics_periodic);

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	/* dont send host command if rf-kill is on */
	if (!iwl_is_ready_rf(priv))
		return;

	iwl_send_statistics_request(priv, CMD_ASYNC, false);
}