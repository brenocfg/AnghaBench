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
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_REVID_ADDR ; 
 int SCA3000_REG_REVID_MAJOR_MASK ; 
 int SCA3000_REG_REVID_MINOR_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_print_rev(struct iio_dev *indio_dev)
{
	int ret;
	struct sca3000_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_REVID_ADDR, 1);
	if (ret < 0)
		goto error_ret;
	dev_info(&indio_dev->dev,
		 "sca3000 revision major=%lu, minor=%lu\n",
		 st->rx[0] & SCA3000_REG_REVID_MAJOR_MASK,
		 st->rx[0] & SCA3000_REG_REVID_MINOR_MASK);
error_ret:
	mutex_unlock(&st->lock);

	return ret;
}