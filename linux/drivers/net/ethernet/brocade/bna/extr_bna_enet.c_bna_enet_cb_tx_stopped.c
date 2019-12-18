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
struct bna_enet {int /*<<< orphan*/  chld_stop_wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

void
bna_enet_cb_tx_stopped(struct bna_enet *enet)
{
	bfa_wc_down(&enet->chld_stop_wc);
}