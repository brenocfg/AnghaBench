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
struct st_uvis25_hw {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ ,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct st_uvis25_hw* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_uvis25_buffer_handler_thread ; 
 int /*<<< orphan*/  st_uvis25_buffer_ops ; 

__attribute__((used)) static int st_uvis25_allocate_buffer(struct iio_dev *iio_dev)
{
	struct st_uvis25_hw *hw = iio_priv(iio_dev);

	return devm_iio_triggered_buffer_setup(regmap_get_device(hw->regmap),
					       iio_dev, NULL,
					       st_uvis25_buffer_handler_thread,
					       &st_uvis25_buffer_ops);
}