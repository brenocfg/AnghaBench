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
struct w5300_priv {scalar_t__ promisc; } ;

/* Variables and functions */
 int IR_S0 ; 
 int /*<<< orphan*/  S0_CR_OPEN ; 
 int S0_IR_RECV ; 
 int S0_IR_SENDOK ; 
 int S0_MR_MACRAW ; 
 int S0_MR_MACRAW_MF ; 
 int /*<<< orphan*/  W5300_IMR ; 
 int /*<<< orphan*/  W5300_S0_IMR ; 
 int /*<<< orphan*/  W5300_S0_MR ; 
 int /*<<< orphan*/  w5300_command (struct w5300_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w5300_hw_start(struct w5300_priv *priv)
{
	w5300_write(priv, W5300_S0_MR, priv->promisc ?
			  S0_MR_MACRAW : S0_MR_MACRAW_MF);
	w5300_command(priv, S0_CR_OPEN);
	w5300_write(priv, W5300_S0_IMR, S0_IR_RECV | S0_IR_SENDOK);
	w5300_write(priv, W5300_IMR, IR_S0);
}