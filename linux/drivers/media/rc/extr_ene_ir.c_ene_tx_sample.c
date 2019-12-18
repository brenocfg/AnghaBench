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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ene_device {int tx_sample_pulse; int tx_sample; scalar_t__ tx_pos; scalar_t__ tx_len; int tx_done; int tx_reg; int /*<<< orphan*/  tx_sim_timer; int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/  tx_complete; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENE_CIRRLC_OUT0 ; 
 int /*<<< orphan*/  ENE_CIRRLC_OUT1 ; 
 scalar_t__ ENE_CIRRLC_OUT_MASK ; 
 int ENE_CIRRLC_OUT_PULSE ; 
 int HZ ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  ene_tx_disable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int min (int,unsigned int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int sample_period ; 
 scalar_t__ txsim ; 

__attribute__((used)) static void ene_tx_sample(struct ene_device *dev)
{
	u8 raw_tx;
	u32 sample;
	bool pulse = dev->tx_sample_pulse;

	if (!dev->tx_buffer) {
		pr_warn("TX: BUG: attempt to transmit NULL buffer\n");
		return;
	}

	/* Grab next TX sample */
	if (!dev->tx_sample) {

		if (dev->tx_pos == dev->tx_len) {
			if (!dev->tx_done) {
				dbg("TX: no more data to send");
				dev->tx_done = true;
				goto exit;
			} else {
				dbg("TX: last sample sent by hardware");
				ene_tx_disable(dev);
				complete(&dev->tx_complete);
				return;
			}
		}

		sample = dev->tx_buffer[dev->tx_pos++];
		dev->tx_sample_pulse = !dev->tx_sample_pulse;

		dev->tx_sample = DIV_ROUND_CLOSEST(sample, sample_period);

		if (!dev->tx_sample)
			dev->tx_sample = 1;
	}

	raw_tx = min(dev->tx_sample , (unsigned int)ENE_CIRRLC_OUT_MASK);
	dev->tx_sample -= raw_tx;

	dbg("TX: sample %8d (%s)", raw_tx * sample_period,
						pulse ? "pulse" : "space");
	if (pulse)
		raw_tx |= ENE_CIRRLC_OUT_PULSE;

	ene_write_reg(dev,
		dev->tx_reg ? ENE_CIRRLC_OUT1 : ENE_CIRRLC_OUT0, raw_tx);

	dev->tx_reg = !dev->tx_reg;
exit:
	/* simulate TX done interrupt */
	if (txsim)
		mod_timer(&dev->tx_sim_timer, jiffies + HZ / 500);
}