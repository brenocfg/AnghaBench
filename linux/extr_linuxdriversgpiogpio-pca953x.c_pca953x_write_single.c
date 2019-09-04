#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int ngpio; } ;
struct pca953x_chip {TYPE_2__* client; TYPE_1__ gpio_chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BANK_SZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int fls (int) ; 
 int i2c_smbus_write_byte_data (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca953x_write_single(struct pca953x_chip *chip, int reg, u32 val,
				int off)
{
	int ret;
	int bank_shift = fls((chip->gpio_chip.ngpio - 1) / BANK_SZ);
	int offset = off / BANK_SZ;

	ret = i2c_smbus_write_byte_data(chip->client,
					(reg << bank_shift) + offset, val);

	if (ret < 0) {
		dev_err(&chip->client->dev, "failed writing register\n");
		return ret;
	}

	return 0;
}