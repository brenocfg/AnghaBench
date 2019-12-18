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
struct st_lsm6dsx_sensor {int odr; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {int dummy; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_read_locked (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int st_lsm6dsx_sensor_set_enable (struct st_lsm6dsx_sensor*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st_lsm6dsx_read_oneshot(struct st_lsm6dsx_sensor *sensor,
				   u8 addr, int *val)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	int err, delay;
	__le16 data;

	err = st_lsm6dsx_sensor_set_enable(sensor, true);
	if (err < 0)
		return err;

	delay = 1000000 / sensor->odr;
	usleep_range(delay, 2 * delay);

	err = st_lsm6dsx_read_locked(hw, addr, &data, sizeof(data));
	if (err < 0)
		return err;

	st_lsm6dsx_sensor_set_enable(sensor, false);

	*val = (s16)le16_to_cpu(data);

	return IIO_VAL_INT;
}