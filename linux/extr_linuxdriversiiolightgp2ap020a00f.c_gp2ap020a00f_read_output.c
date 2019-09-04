#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct gp2ap020a00f_data {int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 int wait_conversion_complete_irq (struct gp2ap020a00f_data*) ; 

__attribute__((used)) static int gp2ap020a00f_read_output(struct gp2ap020a00f_data *data,
					unsigned int output_reg, int *val)
{
	u8 reg_buf[2];
	int err;

	err = wait_conversion_complete_irq(data);
	if (err < 0)
		dev_dbg(&data->client->dev, "data ready timeout\n");

	err = regmap_bulk_read(data->regmap, output_reg, reg_buf, 2);
	if (err < 0)
		return err;

	*val = le16_to_cpup((__le16 *)reg_buf);

	return err;
}