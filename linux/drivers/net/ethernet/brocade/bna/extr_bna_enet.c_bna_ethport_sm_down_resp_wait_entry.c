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
struct bna_ethport {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
bna_ethport_sm_down_resp_wait_entry(struct bna_ethport *ethport)
{
	/**
	 * NOTE: Do not call bna_bfi_ethport_down() here. That will over step
	 * mbox due to up_resp_wait -> down_resp_wait transition on event
	 * ETHPORT_E_DOWN
	 */
}