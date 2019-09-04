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
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int* active_scan_mask; int /*<<< orphan*/  trig; } ;
struct ad799x_state {int id; int config; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  transfer_size; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AD7997_8_READ_SEQUENCE ; 
 int AD7998_CONV_RES_REG ; 
 int AD799X_CHANNEL_SHIFT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  ad7991 135 
#define  ad7992 134 
#define  ad7993 133 
#define  ad7994 132 
#define  ad7995 131 
#define  ad7997 130 
#define  ad7998 129 
#define  ad7999 128 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ad799x_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad799x_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct ad799x_state *st = iio_priv(indio_dev);
	int b_sent;
	u8 cmd;

	switch (st->id) {
	case ad7991:
	case ad7995:
	case ad7999:
		cmd = st->config |
			(*indio_dev->active_scan_mask << AD799X_CHANNEL_SHIFT);
		break;
	case ad7992:
	case ad7993:
	case ad7994:
		cmd = (*indio_dev->active_scan_mask << AD799X_CHANNEL_SHIFT) |
			AD7998_CONV_RES_REG;
		break;
	case ad7997:
	case ad7998:
		cmd = AD7997_8_READ_SEQUENCE | AD7998_CONV_RES_REG;
		break;
	default:
		cmd = 0;
	}

	b_sent = i2c_smbus_read_i2c_block_data(st->client,
			cmd, st->transfer_size, st->rx_buf);
	if (b_sent < 0)
		goto out;

	iio_push_to_buffers_with_timestamp(indio_dev, st->rx_buf,
			iio_get_time_ns(indio_dev));
out:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}