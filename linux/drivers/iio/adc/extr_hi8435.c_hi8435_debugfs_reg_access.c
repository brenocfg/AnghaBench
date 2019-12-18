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
typedef  unsigned int u8 ;
struct iio_dev {int dummy; } ;
struct hi8435_priv {int dummy; } ;

/* Variables and functions */
 int hi8435_readb (struct hi8435_priv*,unsigned int,unsigned int*) ; 
 int hi8435_writeb (struct hi8435_priv*,unsigned int,unsigned int) ; 
 struct hi8435_priv* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int hi8435_debugfs_reg_access(struct iio_dev *idev,
				     unsigned reg, unsigned writeval,
				     unsigned *readval)
{
	struct hi8435_priv *priv = iio_priv(idev);
	int ret;
	u8 val;

	if (readval != NULL) {
		ret = hi8435_readb(priv, reg, &val);
		*readval = val;
	} else {
		val = (u8)writeval;
		ret = hi8435_writeb(priv, reg, val);
	}

	return ret;
}