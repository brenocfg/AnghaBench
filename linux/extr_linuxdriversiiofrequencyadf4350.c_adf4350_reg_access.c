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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct adf4350_state {unsigned int* regs; unsigned int* regs_hw; } ;

/* Variables and functions */
 unsigned int ADF4350_REG5 ; 
 unsigned int BIT (int) ; 
 int EINVAL ; 
 int adf4350_sync_config (struct adf4350_state*) ; 
 struct adf4350_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adf4350_reg_access(struct iio_dev *indio_dev,
			      unsigned reg, unsigned writeval,
			      unsigned *readval)
{
	struct adf4350_state *st = iio_priv(indio_dev);
	int ret;

	if (reg > ADF4350_REG5)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);
	if (readval == NULL) {
		st->regs[reg] = writeval & ~(BIT(0) | BIT(1) | BIT(2));
		ret = adf4350_sync_config(st);
	} else {
		*readval =  st->regs_hw[reg];
		ret = 0;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret;
}