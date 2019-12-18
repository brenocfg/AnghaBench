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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
struct ade7854_state {int (* write_reg ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_reg ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADE7854_CONFIG ; 
 int /*<<< orphan*/  BIT (int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ade7854_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int stub2 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ade7854_reset(struct device *dev)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ade7854_state *st = iio_priv(indio_dev);
	u32 val;

	st->read_reg(dev, ADE7854_CONFIG, &val, 16);
	val |= BIT(7); /* Software Chip Reset */

	return st->write_reg(dev, ADE7854_CONFIG, val, 16);
}