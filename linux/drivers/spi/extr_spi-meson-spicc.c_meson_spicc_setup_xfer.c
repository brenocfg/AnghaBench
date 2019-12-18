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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int /*<<< orphan*/  speed_hz; } ;
struct meson_spicc_device {int bytes_per_word; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPICC_BITLENGTH_MASK ; 
 scalar_t__ SPICC_CONREG ; 
 int /*<<< orphan*/  meson_spicc_setup_speed (struct meson_spicc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_spicc_setup_xfer(struct meson_spicc_device *spicc,
				   struct spi_transfer *xfer)
{
	u32 conf, conf_orig;

	/* Read original configuration */
	conf = conf_orig = readl_relaxed(spicc->base + SPICC_CONREG);

	/* Select closest divider */
	conf = meson_spicc_setup_speed(spicc, conf, xfer->speed_hz);

	/* Setup word width */
	conf &= ~SPICC_BITLENGTH_MASK;
	conf |= FIELD_PREP(SPICC_BITLENGTH_MASK,
			   (spicc->bytes_per_word << 3) - 1);

	/* Ignore if unchanged */
	if (conf != conf_orig)
		writel_relaxed(conf, spicc->base + SPICC_CONREG);
}