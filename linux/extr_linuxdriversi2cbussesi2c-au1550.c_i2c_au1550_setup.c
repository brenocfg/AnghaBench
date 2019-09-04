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
struct i2c_au1550_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CTRL ; 
 unsigned long PSC_CTRL_DISABLE ; 
 unsigned long PSC_CTRL_ENABLE ; 
 unsigned long PSC_CTRL_SUSPEND ; 
 int /*<<< orphan*/  PSC_SEL ; 
 unsigned long PSC_SEL_PS_SMBUSMODE ; 
 int /*<<< orphan*/  PSC_SMBCFG ; 
 unsigned long PSC_SMBCFG_DD_DISABLE ; 
 unsigned long PSC_SMBCFG_DE_ENABLE ; 
 int /*<<< orphan*/  PSC_SMBCFG_DIV8 ; 
 unsigned long PSC_SMBCFG_RT_FIFO8 ; 
 unsigned long PSC_SMBCFG_SET_DIV (int /*<<< orphan*/ ) ; 
 unsigned long PSC_SMBCFG_TT_FIFO8 ; 
 int /*<<< orphan*/  PSC_SMBMSK ; 
 unsigned long PSC_SMBMSK_ALLMASK ; 
 int /*<<< orphan*/  PSC_SMBSTAT ; 
 int PSC_SMBSTAT_SR ; 
 int /*<<< orphan*/  PSC_SMBTMR ; 
 unsigned long PSC_SMBTMR_SET_CH (int) ; 
 unsigned long PSC_SMBTMR_SET_CL (int) ; 
 unsigned long PSC_SMBTMR_SET_PS (int) ; 
 unsigned long PSC_SMBTMR_SET_PU (int) ; 
 unsigned long PSC_SMBTMR_SET_SH (int) ; 
 unsigned long PSC_SMBTMR_SET_SU (int) ; 
 unsigned long PSC_SMBTMR_SET_TH (int /*<<< orphan*/ ) ; 
 int RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR (struct i2c_au1550_data*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void i2c_au1550_setup(struct i2c_au1550_data *priv)
{
	unsigned long cfg;

	WR(priv, PSC_CTRL, PSC_CTRL_DISABLE);
	WR(priv, PSC_SEL, PSC_SEL_PS_SMBUSMODE);
	WR(priv, PSC_SMBCFG, 0);
	WR(priv, PSC_CTRL, PSC_CTRL_ENABLE);
	while ((RD(priv, PSC_SMBSTAT) & PSC_SMBSTAT_SR) == 0)
		cpu_relax();

	cfg = PSC_SMBCFG_RT_FIFO8 | PSC_SMBCFG_TT_FIFO8 | PSC_SMBCFG_DD_DISABLE;
	WR(priv, PSC_SMBCFG, cfg);

	/* Divide by 8 to get a 6.25 MHz clock.  The later protocol
	 * timings are based on this clock.
	 */
	cfg |= PSC_SMBCFG_SET_DIV(PSC_SMBCFG_DIV8);
	WR(priv, PSC_SMBCFG, cfg);
	WR(priv, PSC_SMBMSK, PSC_SMBMSK_ALLMASK);

	/* Set the protocol timer values.  See Table 71 in the
	 * Au1550 Data Book for standard timing values.
	 */
	WR(priv, PSC_SMBTMR, PSC_SMBTMR_SET_TH(0) | PSC_SMBTMR_SET_PS(20) | \
		PSC_SMBTMR_SET_PU(20) | PSC_SMBTMR_SET_SH(20) | \
		PSC_SMBTMR_SET_SU(20) | PSC_SMBTMR_SET_CL(20) | \
		PSC_SMBTMR_SET_CH(20));

	cfg |= PSC_SMBCFG_DE_ENABLE;
	WR(priv, PSC_SMBCFG, cfg);
	while ((RD(priv, PSC_SMBSTAT) & PSC_SMBSTAT_SR) == 0)
		cpu_relax();

	WR(priv, PSC_CTRL, PSC_CTRL_SUSPEND);
}