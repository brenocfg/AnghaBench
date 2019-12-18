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
struct pch_can_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_CAN_NONE ; 
 int /*<<< orphan*/  PCH_CAN_STOP ; 
 int /*<<< orphan*/  pch_can_set_int_enables (struct pch_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_set_run_mode (struct pch_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_set_rx_all (struct pch_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_set_tx_all (struct pch_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_release(struct pch_can_priv *priv)
{
	/* Stooping the CAN device. */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Disabling the interrupts. */
	pch_can_set_int_enables(priv, PCH_CAN_NONE);

	/* Disabling all the receive object. */
	pch_can_set_rx_all(priv, 0);

	/* Disabling all the transmit object. */
	pch_can_set_tx_all(priv, 0);
}