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
struct gs_tx_context {int /*<<< orphan*/  echo_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_MAX_TX_URBS ; 

__attribute__((used)) static void gs_free_tx_context(struct gs_tx_context *txc)
{
	txc->echo_id = GS_MAX_TX_URBS;
}