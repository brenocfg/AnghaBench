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
struct da9150 {int /*<<< orphan*/  dev; int /*<<< orphan*/  core_qif; } ;

/* Variables and functions */
 int da9150_i2c_write_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

void da9150_write_qif(struct da9150 *da9150, u8 addr, int count, const u8 *buf)
{
	int ret;

	ret = da9150_i2c_write_device(da9150->core_qif, addr, count, buf);
	if (ret < 0)
		dev_err(da9150->dev, "Failed to write to QIF 0x%x: %d\n",
			addr, ret);
}