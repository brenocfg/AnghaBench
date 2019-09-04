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
struct iio_chan_spec {scalar_t__ scan_index; } ;
struct adis16400_state {int /*<<< orphan*/ * avail_scan_mask; struct adis16400_chip_info* variant; } ;
struct adis16400_chip_info {unsigned int num_channels; struct iio_chan_spec* channels; } ;

/* Variables and functions */
 scalar_t__ ADIS16400_SCAN_TIMESTAMP ; 
 int /*<<< orphan*/  BIT (scalar_t__) ; 

__attribute__((used)) static void adis16400_setup_chan_mask(struct adis16400_state *st)
{
	const struct adis16400_chip_info *chip_info = st->variant;
	unsigned int i;

	for (i = 0; i < chip_info->num_channels; i++) {
		const struct iio_chan_spec *ch = &chip_info->channels[i];

		if (ch->scan_index >= 0 &&
		    ch->scan_index != ADIS16400_SCAN_TIMESTAMP)
			st->avail_scan_mask[0] |= BIT(ch->scan_index);
	}
}