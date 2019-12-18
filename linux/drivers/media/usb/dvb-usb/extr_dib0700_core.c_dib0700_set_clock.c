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
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; struct dib0700_state* priv; } ;
struct dib0700_state {int* buf; } ;

/* Variables and functions */
 int EINTR ; 
 int REQUEST_SET_CLOCK ; 
 int dib0700_ctrl_wr (struct dvb_usb_device*,int*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib0700_set_clock(struct dvb_usb_device *d, u8 en_pll,
	u8 pll_src, u8 pll_range, u8 clock_gpio3, u16 pll_prediv,
	u16 pll_loopdiv, u16 free_div, u16 dsuScaler)
{
	struct dib0700_state *st = d->priv;
	int ret;

	if (mutex_lock_interruptible(&d->usb_mutex) < 0) {
		err("could not acquire lock");
		return -EINTR;
	}

	st->buf[0] = REQUEST_SET_CLOCK;
	st->buf[1] = (en_pll << 7) | (pll_src << 6) |
		(pll_range << 5) | (clock_gpio3 << 4);
	st->buf[2] = (pll_prediv >> 8)  & 0xff; /* MSB */
	st->buf[3] =  pll_prediv        & 0xff; /* LSB */
	st->buf[4] = (pll_loopdiv >> 8) & 0xff; /* MSB */
	st->buf[5] =  pll_loopdiv       & 0xff; /* LSB */
	st->buf[6] = (free_div >> 8)    & 0xff; /* MSB */
	st->buf[7] =  free_div          & 0xff; /* LSB */
	st->buf[8] = (dsuScaler >> 8)   & 0xff; /* MSB */
	st->buf[9] =  dsuScaler         & 0xff; /* LSB */

	ret = dib0700_ctrl_wr(d, st->buf, 10);
	mutex_unlock(&d->usb_mutex);

	return ret;
}