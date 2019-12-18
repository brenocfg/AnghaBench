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
struct ad7192_state {int /*<<< orphan*/  conf; int /*<<< orphan*/  sd; int /*<<< orphan*/  mode; void* f_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7192_CONF_CHOP ; 
 int /*<<< orphan*/  AD7192_MODE_SINC3 ; 
 void* AD7192_NO_SYNC_FILTER ; 
 int /*<<< orphan*/  AD7192_REG_CONF ; 
 int /*<<< orphan*/  AD7192_REG_MODE ; 
 void* AD7192_SYNC3_FILTER ; 
 void* AD7192_SYNC4_FILTER ; 
 int ARRAY_SIZE (int*) ; 
 unsigned int U32_MAX ; 
 unsigned int abs (int) ; 
 int /*<<< orphan*/  ad7192_get_available_filter_freq (struct ad7192_state*,int*) ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7192_set_3db_filter_freq(struct ad7192_state *st,
				      int val, int val2)
{
	int freq_avail[4], i, ret, freq;
	unsigned int diff_new, diff_old;
	int idx = 0;

	diff_old = U32_MAX;
	freq = val * 1000 + val2;

	ad7192_get_available_filter_freq(st, freq_avail);

	for (i = 0; i < ARRAY_SIZE(freq_avail); i++) {
		diff_new = abs(freq - freq_avail[i]);
		if (diff_new < diff_old) {
			diff_old = diff_new;
			idx = i;
		}
	}

	switch (idx) {
	case 0:
		st->f_order = AD7192_SYNC4_FILTER;
		st->mode &= ~AD7192_MODE_SINC3;

		st->conf |= AD7192_CONF_CHOP;
		break;
	case 1:
		st->f_order = AD7192_SYNC3_FILTER;
		st->mode |= AD7192_MODE_SINC3;

		st->conf |= AD7192_CONF_CHOP;
		break;
	case 2:
		st->f_order = AD7192_NO_SYNC_FILTER;
		st->mode &= ~AD7192_MODE_SINC3;

		st->conf &= ~AD7192_CONF_CHOP;
		break;
	case 3:
		st->f_order = AD7192_NO_SYNC_FILTER;
		st->mode |= AD7192_MODE_SINC3;

		st->conf &= ~AD7192_CONF_CHOP;
		break;
	}

	ret = ad_sd_write_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
	if (ret < 0)
		return ret;

	return ad_sd_write_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
}