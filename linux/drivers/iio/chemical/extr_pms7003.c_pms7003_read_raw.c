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
struct pms7003_frame {scalar_t__ data; } ;
struct pms7003_state {int /*<<< orphan*/  lock; struct pms7003_frame frame; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ address; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_PASSIVE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_MASSCONCENTRATION 128 
 int IIO_VAL_INT ; 
 struct pms7003_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pms7003_do_cmd (struct pms7003_state*,int /*<<< orphan*/ ) ; 
 int pms7003_get_pm (scalar_t__) ; 

__attribute__((used)) static int pms7003_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct pms7003_state *state = iio_priv(indio_dev);
	struct pms7003_frame *frame = &state->frame;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_MASSCONCENTRATION:
			mutex_lock(&state->lock);
			ret = pms7003_do_cmd(state, CMD_READ_PASSIVE);
			if (ret) {
				mutex_unlock(&state->lock);
				return ret;
			}

			*val = pms7003_get_pm(frame->data + chan->address);
			mutex_unlock(&state->lock);

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	}

	return -EINVAL;
}