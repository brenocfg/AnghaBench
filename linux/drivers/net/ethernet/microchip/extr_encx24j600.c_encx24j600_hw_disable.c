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
struct encx24j600_priv {int hw_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLERX ; 
 int /*<<< orphan*/  EIE ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encx24j600_hw_disable(struct encx24j600_priv *priv)
{
	/* Disable all interrupts */
	encx24j600_write_reg(priv, EIE, 0);

	/* Disable RX */
	encx24j600_cmd(priv, DISABLERX);

	priv->hw_enabled = false;
}