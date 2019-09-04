#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max1363_state {int (* recv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ;int /*<<< orphan*/  client; TYPE_2__* chip_info; TYPE_1__* current_mode; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; scalar_t__ scan_timestamp; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {int bits; } ;
struct TYPE_3__ {int /*<<< orphan*/  modemask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MAX1363_MAX_CHANNELS ; 
 unsigned long bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct max1363_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t max1363_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct max1363_state *st = iio_priv(indio_dev);
	__u8 *rxbuf;
	int b_sent;
	size_t d_size;
	unsigned long numvals = bitmap_weight(st->current_mode->modemask,
					      MAX1363_MAX_CHANNELS);

	/* Ensure the timestamp is 8 byte aligned */
	if (st->chip_info->bits != 8)
		d_size = numvals*2;
	else
		d_size = numvals;
	if (indio_dev->scan_timestamp) {
		d_size += sizeof(s64);
		if (d_size % sizeof(s64))
			d_size += sizeof(s64) - (d_size % sizeof(s64));
	}
	/* Monitor mode prevents reading. Whilst not currently implemented
	 * might as well have this test in here in the meantime as it does
	 * no harm.
	 */
	if (numvals == 0)
		goto done;

	rxbuf = kmalloc(d_size,	GFP_KERNEL);
	if (rxbuf == NULL)
		goto done;
	if (st->chip_info->bits != 8)
		b_sent = st->recv(st->client, rxbuf, numvals * 2);
	else
		b_sent = st->recv(st->client, rxbuf, numvals);
	if (b_sent < 0)
		goto done_free;

	iio_push_to_buffers_with_timestamp(indio_dev, rxbuf,
					   iio_get_time_ns(indio_dev));

done_free:
	kfree(rxbuf);
done:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}