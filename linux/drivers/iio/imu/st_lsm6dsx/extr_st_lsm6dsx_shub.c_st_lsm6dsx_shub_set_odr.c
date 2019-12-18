#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {struct st_lsm6dsx_ext_dev_settings* settings; } ;
struct st_lsm6dsx_sensor {TYPE_1__ ext_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ reg; } ;
struct st_lsm6dsx_ext_dev_settings {TYPE_3__ odr_table; } ;

/* Variables and functions */
 int st_lsm6dsx_shub_get_odr_val (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_shub_write_with_mask (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
st_lsm6dsx_shub_set_odr(struct st_lsm6dsx_sensor *sensor, u16 odr)
{
	const struct st_lsm6dsx_ext_dev_settings *settings;
	u16 val;
	int err;

	err = st_lsm6dsx_shub_get_odr_val(sensor, odr, &val);
	if (err < 0)
		return err;

	settings = sensor->ext_info.settings;
	return st_lsm6dsx_shub_write_with_mask(sensor,
					       settings->odr_table.reg.addr,
					       settings->odr_table.reg.mask,
					       val);
}