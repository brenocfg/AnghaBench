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
typedef  int u8 ;
struct max1363_state {int setupbyte; int configbyte; int monitor_on; int mask_low; int mask_high; int monitor_speed; int* thresh_low; int* thresh_high; int (* send ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int conf; long* modemask; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX1363_CHANNEL_SEL_MASK ; 
 int MAX1363_CONFIG_SCAN_MONITOR_MODE ; 
 int /*<<< orphan*/  MAX1363_MAX_CHANNELS ; 
 int MAX1363_MON_INT_ENABLE ; 
 int MAX1363_SCAN_MASK ; 
 int MAX1363_SETUP_MONITOR_SETUP ; 
 int MAX1363_SE_DE_MASK ; 
 unsigned long bitmap_weight (long const*,int /*<<< orphan*/ ) ; 
 size_t d0m1to2m3 ; 
 size_t d1m0to3m2 ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* max1363_mode_table ; 
 int max1363_write_basic_config (struct max1363_state*) ; 
 size_t s0to3 ; 
 int stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int stub2 (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ test_bit (int,long const*) ; 

__attribute__((used)) static int max1363_monitor_mode_update(struct max1363_state *st, int enabled)
{
	u8 *tx_buf;
	int ret, i = 3, j;
	unsigned long numelements;
	int len;
	const long *modemask;

	if (!enabled) {
		/* transition to buffered capture is not currently supported */
		st->setupbyte &= ~MAX1363_SETUP_MONITOR_SETUP;
		st->configbyte &= ~MAX1363_SCAN_MASK;
		st->monitor_on = false;
		return max1363_write_basic_config(st);
	}

	/* Ensure we are in the relevant mode */
	st->setupbyte |= MAX1363_SETUP_MONITOR_SETUP;
	st->configbyte &= ~(MAX1363_CHANNEL_SEL_MASK
			    | MAX1363_SCAN_MASK
			| MAX1363_SE_DE_MASK);
	st->configbyte |= MAX1363_CONFIG_SCAN_MONITOR_MODE;
	if ((st->mask_low | st->mask_high) & 0x0F) {
		st->configbyte |= max1363_mode_table[s0to3].conf;
		modemask = max1363_mode_table[s0to3].modemask;
	} else if ((st->mask_low | st->mask_high) & 0x30) {
		st->configbyte |= max1363_mode_table[d0m1to2m3].conf;
		modemask = max1363_mode_table[d0m1to2m3].modemask;
	} else {
		st->configbyte |= max1363_mode_table[d1m0to3m2].conf;
		modemask = max1363_mode_table[d1m0to3m2].modemask;
	}
	numelements = bitmap_weight(modemask, MAX1363_MAX_CHANNELS);
	len = 3 * numelements + 3;
	tx_buf = kmalloc(len, GFP_KERNEL);
	if (!tx_buf) {
		ret = -ENOMEM;
		goto error_ret;
	}
	tx_buf[0] = st->configbyte;
	tx_buf[1] = st->setupbyte;
	tx_buf[2] = (st->monitor_speed << 1);

	/*
	 * So we need to do yet another bit of nefarious scan mode
	 * setup to match what we need.
	 */
	for (j = 0; j < 8; j++)
		if (test_bit(j, modemask)) {
			/* Establish the mode is in the scan */
			if (st->mask_low & (1 << j)) {
				tx_buf[i] = (st->thresh_low[j] >> 4) & 0xFF;
				tx_buf[i + 1] = (st->thresh_low[j] << 4) & 0xF0;
			} else if (j < 4) {
				tx_buf[i] = 0;
				tx_buf[i + 1] = 0;
			} else {
				tx_buf[i] = 0x80;
				tx_buf[i + 1] = 0;
			}
			if (st->mask_high & (1 << j)) {
				tx_buf[i + 1] |=
					(st->thresh_high[j] >> 8) & 0x0F;
				tx_buf[i + 2] = st->thresh_high[j] & 0xFF;
			} else if (j < 4) {
				tx_buf[i + 1] |= 0x0F;
				tx_buf[i + 2] = 0xFF;
			} else {
				tx_buf[i + 1] |= 0x07;
				tx_buf[i + 2] = 0xFF;
			}
			i += 3;
		}


	ret = st->send(st->client, tx_buf, len);
	if (ret < 0)
		goto error_ret;
	if (ret != len) {
		ret = -EIO;
		goto error_ret;
	}

	/*
	 * Now that we hopefully have sensible thresholds in place it is
	 * time to turn the interrupts on.
	 * It is unclear from the data sheet if this should be necessary
	 * (i.e. whether monitor mode setup is atomic) but it appears to
	 * be in practice.
	 */
	tx_buf[0] = st->setupbyte;
	tx_buf[1] = MAX1363_MON_INT_ENABLE | (st->monitor_speed << 1) | 0xF0;
	ret = st->send(st->client, tx_buf, 2);
	if (ret < 0)
		goto error_ret;
	if (ret != 2) {
		ret = -EIO;
		goto error_ret;
	}
	ret = 0;
	st->monitor_on = true;
error_ret:

	kfree(tx_buf);

	return ret;
}