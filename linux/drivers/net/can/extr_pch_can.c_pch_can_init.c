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
 int /*<<< orphan*/  PCH_CAN_ALL ; 
 int /*<<< orphan*/  PCH_CAN_STOP ; 
 int /*<<< orphan*/  pch_can_clear_if_buffers (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pch_can_config_rx_tx_buffers (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pch_can_set_int_enables (struct pch_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_set_run_mode (struct pch_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_init(struct pch_can_priv *priv)
{
	/* Stopping the Can device. */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Clearing all the message object buffers. */
	pch_can_clear_if_buffers(priv);

	/* Configuring the respective message object as either rx/tx object. */
	pch_can_config_rx_tx_buffers(priv);

	/* Enabling the interrupts. */
	pch_can_set_int_enables(priv, PCH_CAN_ALL);
}