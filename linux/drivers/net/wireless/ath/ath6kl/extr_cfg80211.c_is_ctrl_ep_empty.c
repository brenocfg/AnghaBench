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
struct ath6kl {size_t ctrl_ep; int /*<<< orphan*/ * tx_pending; } ;

/* Variables and functions */

__attribute__((used)) static bool is_ctrl_ep_empty(struct ath6kl *ar)
{
	return !ar->tx_pending[ar->ctrl_ep];
}