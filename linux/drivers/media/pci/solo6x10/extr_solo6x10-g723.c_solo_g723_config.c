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
struct solo_dev {int clock_mhz; } ;

/* Variables and functions */
 int BITRATE ; 
 int /*<<< orphan*/  G723_INTR_ORDER ; 
 int /*<<< orphan*/  OUTMODE_MASK ; 
 int SAMPLERATE ; 
 int SOLO_AUDIO_BITRATE (int) ; 
 int SOLO_AUDIO_CLK_DIV (int) ; 
 int /*<<< orphan*/  SOLO_AUDIO_CONTROL ; 
 int SOLO_AUDIO_ENABLE ; 
 int SOLO_AUDIO_FDMA_BASE (int) ; 
 int SOLO_AUDIO_FDMA_INTERVAL (int) ; 
 int /*<<< orphan*/  SOLO_AUDIO_FDMA_INTR ; 
 int SOLO_AUDIO_I2S_MODE ; 
 int SOLO_AUDIO_I2S_MULTI (int) ; 
 int SOLO_AUDIO_INTR_ORDER (int /*<<< orphan*/ ) ; 
 int SOLO_AUDIO_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_AUDIO_SAMPLE ; 
 int SOLO_G723_EXT_ADDR (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_g723_config(struct solo_dev *solo_dev)
{
	int clk_div;

	clk_div = (solo_dev->clock_mhz * 1000000)
		/ (SAMPLERATE * (BITRATE * 2) * 2);

	solo_reg_write(solo_dev, SOLO_AUDIO_SAMPLE,
		       SOLO_AUDIO_BITRATE(BITRATE)
		       | SOLO_AUDIO_CLK_DIV(clk_div));

	solo_reg_write(solo_dev, SOLO_AUDIO_FDMA_INTR,
		       SOLO_AUDIO_FDMA_INTERVAL(1)
		       | SOLO_AUDIO_INTR_ORDER(G723_INTR_ORDER)
		       | SOLO_AUDIO_FDMA_BASE(SOLO_G723_EXT_ADDR(solo_dev) >> 16));

	solo_reg_write(solo_dev, SOLO_AUDIO_CONTROL,
		       SOLO_AUDIO_ENABLE
		       | SOLO_AUDIO_I2S_MODE
		       | SOLO_AUDIO_I2S_MULTI(3)
		       | SOLO_AUDIO_MODE(OUTMODE_MASK));
}