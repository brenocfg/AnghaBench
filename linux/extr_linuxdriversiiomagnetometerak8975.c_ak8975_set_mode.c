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
struct ak8975_data {int cntl_cache; TYPE_1__* def; int /*<<< orphan*/  client; } ;
typedef  enum ak_ctrl_mode { ____Placeholder_ak_ctrl_mode } ak_ctrl_mode ;
struct TYPE_2__ {int* ctrl_masks; int* ctrl_modes; int /*<<< orphan*/ * ctrl_regs; } ;

/* Variables and functions */
 size_t CNTL ; 
 size_t CNTL_MODE ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ak8975_set_mode(struct ak8975_data *data, enum ak_ctrl_mode mode)
{
	u8 regval;
	int ret;

	regval = (data->cntl_cache & ~data->def->ctrl_masks[CNTL_MODE]) |
		 data->def->ctrl_modes[mode];
	ret = i2c_smbus_write_byte_data(data->client,
					data->def->ctrl_regs[CNTL], regval);
	if (ret < 0) {
		return ret;
	}
	data->cntl_cache = regval;
	/* After mode change wait atleast 100us */
	usleep_range(100, 500);

	return 0;
}