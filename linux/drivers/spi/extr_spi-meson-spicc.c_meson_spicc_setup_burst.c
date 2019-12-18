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
struct meson_spicc_device {unsigned int tx_remain; unsigned int rx_remain; unsigned int bytes_per_word; int is_burst_end; int is_last_burst; scalar_t__ base; scalar_t__ xfer_remain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SPICC_BURSTLENGTH_MASK ; 
 unsigned int SPICC_BURST_MAX ; 
 scalar_t__ SPICC_CONREG ; 
 int /*<<< orphan*/  meson_spicc_tx (struct meson_spicc_device*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void meson_spicc_setup_burst(struct meson_spicc_device *spicc,
					   unsigned int burst_len)
{
	/* Setup Xfer variables */
	spicc->tx_remain = burst_len;
	spicc->rx_remain = burst_len;
	spicc->xfer_remain -= burst_len * spicc->bytes_per_word;
	spicc->is_burst_end = false;
	if (burst_len < SPICC_BURST_MAX || !spicc->xfer_remain)
		spicc->is_last_burst = true;
	else
		spicc->is_last_burst = false;

	/* Setup burst length */
	writel_bits_relaxed(SPICC_BURSTLENGTH_MASK,
			FIELD_PREP(SPICC_BURSTLENGTH_MASK,
				burst_len),
			spicc->base + SPICC_CONREG);

	/* Fill TX FIFO */
	meson_spicc_tx(spicc);
}