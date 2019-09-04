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
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int AUDIO_DIV_SERCLK_8 ; 
 int /*<<< orphan*/  MAIN_CNTRL0_SR ; 
 int PLL_SERIAL_2_SRL_NOSC (int) ; 
 int /*<<< orphan*/  REG_AUDIO_DIV ; 
 int /*<<< orphan*/  REG_BUFFER_OUT ; 
 int /*<<< orphan*/  REG_MAIN_CNTRL0 ; 
 int /*<<< orphan*/  REG_MUX_VP_VIP_OUT ; 
 int /*<<< orphan*/  REG_PLL_SCG1 ; 
 int /*<<< orphan*/  REG_PLL_SCG2 ; 
 int /*<<< orphan*/  REG_PLL_SCGN1 ; 
 int /*<<< orphan*/  REG_PLL_SCGN2 ; 
 int /*<<< orphan*/  REG_PLL_SCGR1 ; 
 int /*<<< orphan*/  REG_PLL_SCGR2 ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_1 ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_2 ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_3 ; 
 int /*<<< orphan*/  REG_SEL_CLK ; 
 int /*<<< orphan*/  REG_SERIALIZER ; 
 int /*<<< orphan*/  REG_SOFTRESET ; 
 int SEL_CLK_ENA_SC_CLK ; 
 int SEL_CLK_SEL_CLK1 ; 
 int SOFTRESET_AUDIO ; 
 int SOFTRESET_I2C_MASTER ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tda998x_reset(struct tda998x_priv *priv)
{
	/* reset audio and i2c master: */
	reg_write(priv, REG_SOFTRESET, SOFTRESET_AUDIO | SOFTRESET_I2C_MASTER);
	msleep(50);
	reg_write(priv, REG_SOFTRESET, 0);
	msleep(50);

	/* reset transmitter: */
	reg_set(priv, REG_MAIN_CNTRL0, MAIN_CNTRL0_SR);
	reg_clear(priv, REG_MAIN_CNTRL0, MAIN_CNTRL0_SR);

	/* PLL registers common configuration */
	reg_write(priv, REG_PLL_SERIAL_1, 0x00);
	reg_write(priv, REG_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(1));
	reg_write(priv, REG_PLL_SERIAL_3, 0x00);
	reg_write(priv, REG_SERIALIZER,   0x00);
	reg_write(priv, REG_BUFFER_OUT,   0x00);
	reg_write(priv, REG_PLL_SCG1,     0x00);
	reg_write(priv, REG_AUDIO_DIV,    AUDIO_DIV_SERCLK_8);
	reg_write(priv, REG_SEL_CLK,      SEL_CLK_SEL_CLK1 | SEL_CLK_ENA_SC_CLK);
	reg_write(priv, REG_PLL_SCGN1,    0xfa);
	reg_write(priv, REG_PLL_SCGN2,    0x00);
	reg_write(priv, REG_PLL_SCGR1,    0x5b);
	reg_write(priv, REG_PLL_SCGR2,    0x00);
	reg_write(priv, REG_PLL_SCG2,     0x10);

	/* Write the default value MUX register */
	reg_write(priv, REG_MUX_VP_VIP_OUT, 0x24);
}