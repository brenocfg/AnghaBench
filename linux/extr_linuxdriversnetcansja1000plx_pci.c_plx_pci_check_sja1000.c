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
struct sja1000_priv {int (* read_reg ) (struct sja1000_priv const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDR_PELICAN ; 
 int /*<<< orphan*/  REG_CR ; 
 int REG_CR_BASICCAN_INITIAL ; 
 int REG_CR_BASICCAN_INITIAL_MASK ; 
 int REG_IR_BASICCAN_INITIAL ; 
 int REG_IR_PELICAN_INITIAL ; 
 int REG_MOD_PELICAN_INITIAL ; 
 int REG_SR_BASICCAN_INITIAL ; 
 int REG_SR_PELICAN_INITIAL ; 
 int /*<<< orphan*/  SJA1000_CDR ; 
 int /*<<< orphan*/  SJA1000_IR ; 
 int /*<<< orphan*/  SJA1000_MOD ; 
 int /*<<< orphan*/  SJA1000_SR ; 
 int stub1 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 
 int stub2 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 
 int stub3 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct sja1000_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub5 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 
 int stub6 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 
 int stub7 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int plx_pci_check_sja1000(const struct sja1000_priv *priv)
{
	int flag = 0;

	/*
	 * Check registers after hardware reset (the Basic mode)
	 * See states on p. 10 of the Datasheet.
	 */
	if ((priv->read_reg(priv, REG_CR) & REG_CR_BASICCAN_INITIAL_MASK) ==
	    REG_CR_BASICCAN_INITIAL &&
	    (priv->read_reg(priv, SJA1000_SR) == REG_SR_BASICCAN_INITIAL) &&
	    (priv->read_reg(priv, SJA1000_IR) == REG_IR_BASICCAN_INITIAL))
		flag = 1;

	/* Bring the SJA1000 into the PeliCAN mode*/
	priv->write_reg(priv, SJA1000_CDR, CDR_PELICAN);

	/*
	 * Check registers after reset in the PeliCAN mode.
	 * See states on p. 23 of the Datasheet.
	 */
	if (priv->read_reg(priv, SJA1000_MOD) == REG_MOD_PELICAN_INITIAL &&
	    priv->read_reg(priv, SJA1000_SR) == REG_SR_PELICAN_INITIAL &&
	    priv->read_reg(priv, SJA1000_IR) == REG_IR_PELICAN_INITIAL)
		return flag;

	return 0;
}