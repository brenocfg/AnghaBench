#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct bcm2835_host {int overclock_50; int cdiv; unsigned int max_clk; int ns_per_fifo_word; unsigned int overclock; unsigned int user_overclock_50; unsigned int clock; int /*<<< orphan*/  lock; scalar_t__ reset_clock; TYPE_1__* mmc; scalar_t__ debug; scalar_t__ firmware_sets_cdiv; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {unsigned int actual_clock; int caps; } ;

/* Variables and functions */
 int MHZ ; 
 int MMC_CAP_4_BIT_DATA ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_SDHOST_CLOCK ; 
 int /*<<< orphan*/  SDCDIV ; 
 int SDCDIV_MAX_CDIV ; 
 int /*<<< orphan*/  SDTOUT ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpi_firmware_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int**,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void bcm2835_sdhost_set_clock(struct bcm2835_host *host, unsigned int clock)
{
	int div = 0; /* Initialized for compiler warning */
	unsigned int input_clock = clock;
	unsigned long flags;

	if (host->debug)
		pr_info("%s: set_clock(%d)\n", mmc_hostname(host->mmc), clock);

	if (host->overclock_50 && (clock == 50*MHZ))
		clock = host->overclock_50 * MHZ + (MHZ - 1);

	/* The SDCDIV register has 11 bits, and holds (div - 2).
	   But in data mode the max is 50MHz wihout a minimum, and only the
	   bottom 3 bits are used. Since the switch over is automatic (unless
	   we have marked the card as slow...), chosen values have to make
	   sense in both modes.
	   Ident mode must be 100-400KHz, so can range check the requested
	   clock. CMD15 must be used to return to data mode, so this can be
	   monitored.

	   clock 250MHz -> 0->125MHz, 1->83.3MHz, 2->62.5MHz, 3->50.0MHz
                           4->41.7MHz, 5->35.7MHz, 6->31.3MHz, 7->27.8MHz

			 623->400KHz/27.8MHz
			 reset value (507)->491159/50MHz

	   BUT, the 3-bit clock divisor in data mode is too small if the
	   core clock is higher than 250MHz, so instead use the SLOW_CARD
	   configuration bit to force the use of the ident clock divisor
	   at all times.
	*/

	host->mmc->actual_clock = 0;

	if (host->firmware_sets_cdiv) {
		u32 msg[3] = { clock, 0, 0 };

		rpi_firmware_property(rpi_firmware_get(NULL),
				      RPI_FIRMWARE_SET_SDHOST_CLOCK,
				      &msg, sizeof(msg));

		clock = max(msg[1], msg[2]);
		spin_lock_irqsave(&host->lock, flags);
	} else {
		spin_lock_irqsave(&host->lock, flags);
		if (clock < 100000) {
			/* Can't stop the clock, but make it as slow as
			 * possible to show willing
			 */
			host->cdiv = SDCDIV_MAX_CDIV;
			bcm2835_sdhost_write(host, host->cdiv, SDCDIV);
			mmiowb();
			spin_unlock_irqrestore(&host->lock, flags);
			return;
		}

		div = host->max_clk / clock;
		if (div < 2)
			div = 2;
		if ((host->max_clk / div) > clock)
			div++;
		div -= 2;

		if (div > SDCDIV_MAX_CDIV)
			div = SDCDIV_MAX_CDIV;

		clock = host->max_clk / (div + 2);

		host->cdiv = div;
		bcm2835_sdhost_write(host, host->cdiv, SDCDIV);

		if (host->debug)
			pr_info("%s: clock=%d -> max_clk=%d, cdiv=%x "
				"(actual clock %d)\n",
				mmc_hostname(host->mmc), input_clock,
				host->max_clk, host->cdiv,
				clock);
	}

	/* Calibrate some delays */

	host->ns_per_fifo_word = (1000000000/clock) *
		((host->mmc->caps & MMC_CAP_4_BIT_DATA) ? 8 : 32);

	if (input_clock == 50 * MHZ) {
		if (clock > input_clock) {
			/* Save the closest value, to make it easier
			   to reduce in the event of error */
			host->overclock_50 = (clock/MHZ);

			if (clock != host->overclock) {
				pr_info("%s: overclocking to %dHz\n",
					mmc_hostname(host->mmc), clock);
				host->overclock = clock;
			}
		} else if (host->overclock) {
			host->overclock = 0;
			if (clock == 50 * MHZ)
				pr_warn("%s: cancelling overclock\n",
					mmc_hostname(host->mmc));
		}
	} else if (input_clock == 0) {
		/* Reset the preferred overclock when the clock is stopped.
		 * This always happens during initialisation. */
		host->overclock_50 = host->user_overclock_50;
		host->overclock = 0;
	}

	/* Set the timeout to 500ms */
	bcm2835_sdhost_write(host, clock/2, SDTOUT);

	host->mmc->actual_clock = clock;
	host->clock = input_clock;
	host->reset_clock = 0;

	mmiowb();
	spin_unlock_irqrestore(&host->lock, flags);
}