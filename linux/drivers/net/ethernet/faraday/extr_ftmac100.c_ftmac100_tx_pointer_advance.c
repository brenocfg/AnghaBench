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
struct ftmac100 {int /*<<< orphan*/  tx_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftmac100_next_tx_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftmac100_tx_pointer_advance(struct ftmac100 *priv)
{
	priv->tx_pointer = ftmac100_next_tx_pointer(priv->tx_pointer);
}