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
struct mxc4005_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mxc4005_read_axis(struct mxc4005_data *data,
			     unsigned int addr)
{
	__be16 reg;
	int ret;

	ret = regmap_bulk_read(data->regmap, addr, (u8 *) &reg, sizeof(reg));
	if (ret < 0) {
		dev_err(data->dev, "failed to read reg %02x\n", addr);
		return ret;
	}

	return be16_to_cpu(reg);
}