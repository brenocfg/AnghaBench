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
typedef  int u8 ;
struct bh1780_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BH1780_CMD_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_word_data (TYPE_1__*,int) ; 

__attribute__((used)) static int bh1780_read_word(struct bh1780_data *bh1780, u8 reg)
{
	int ret = i2c_smbus_read_word_data(bh1780->client,
					   BH1780_CMD_BIT | reg);
	if (ret < 0)
		dev_err(&bh1780->client->dev,
			"i2c_smbus_read_word_data failed error "
			"%d, register %01x\n",
			ret, reg);
	return ret;
}