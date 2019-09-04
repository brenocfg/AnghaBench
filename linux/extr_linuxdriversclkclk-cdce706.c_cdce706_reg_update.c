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
struct cdce706_dev_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int cdce706_reg_update(struct cdce706_dev_data *dev_data, unsigned reg,
			      unsigned mask, unsigned val)
{
	int rc = regmap_update_bits(dev_data->regmap, reg | 0x80, mask, val);

	if (rc < 0)
		dev_err(&dev_data->client->dev, "error updating reg %u", reg);
	return rc;
}