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
struct cxd2841er_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SLVT ; 
 int /*<<< orphan*/  cxd2841er_write_reg (struct cxd2841er_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int cxd2841er_freeze_regs(struct cxd2841er_priv *priv)
{
	/*
	 * Freeze registers: ensure multiple separate register reads
	 * are from the same snapshot
	 */
	cxd2841er_write_reg(priv, I2C_SLVT, 0x01, 0x01);
	return 0;
}