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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITG3200_DLPF_FS_SEL_2000 ; 
 int /*<<< orphan*/  ITG3200_REG_DLPF ; 
 int itg3200_read_reg_8 (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int itg3200_write_reg_8 (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int itg3200_enable_full_scale(struct iio_dev *indio_dev)
{
	u8 val;
	int ret;

	ret = itg3200_read_reg_8(indio_dev, ITG3200_REG_DLPF, &val);
	if (ret)
		goto err_ret;

	val |= ITG3200_DLPF_FS_SEL_2000;
	return itg3200_write_reg_8(indio_dev, ITG3200_REG_DLPF, val);

err_ret:
	return ret;
}