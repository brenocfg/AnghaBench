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
struct iio_chan_spec {int indexed; int channel; int /*<<< orphan*/  info_mask_separate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_PROCESSED ; 
 int /*<<< orphan*/  IIO_TEMP ; 

__attribute__((used)) static void stmpe_adc_temp_chan(struct iio_chan_spec *ics, int chan)
{
	ics->type = IIO_TEMP;
	ics->info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED);
	ics->indexed = 1;
	ics->channel = chan;
}