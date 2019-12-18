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
struct noa1305_priv {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_LIGHT 128 
 int IIO_VAL_INT ; 
 struct noa1305_priv* iio_priv (struct iio_dev*) ; 
 int noa1305_measure (struct noa1305_priv*) ; 
 int noa1305_scale (struct noa1305_priv*,int*,int*) ; 

__attribute__((used)) static int noa1305_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	int ret = -EINVAL;
	struct noa1305_priv *priv = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			ret = noa1305_measure(priv);
			if (ret < 0)
				return ret;
			*val = ret;
			return IIO_VAL_INT;
		default:
			break;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_LIGHT:
			return noa1305_scale(priv, val, val2);
		default:
			break;
		}
		break;
	default:
		break;
	}

	return ret;
}