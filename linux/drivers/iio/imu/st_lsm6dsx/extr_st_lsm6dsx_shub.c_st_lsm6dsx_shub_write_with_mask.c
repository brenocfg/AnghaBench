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
typedef  int u8 ;
struct st_lsm6dsx_sensor {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int __ffs (int) ; 
 int st_lsm6dsx_shub_read (struct st_lsm6dsx_sensor*,int,int*,int) ; 
 int st_lsm6dsx_shub_write (struct st_lsm6dsx_sensor*,int,int*,int) ; 

__attribute__((used)) static int
st_lsm6dsx_shub_write_with_mask(struct st_lsm6dsx_sensor *sensor,
				u8 addr, u8 mask, u8 val)
{
	int err;
	u8 data;

	err = st_lsm6dsx_shub_read(sensor, addr, &data, sizeof(data));
	if (err < 0)
		return err;

	data = ((data & ~mask) | (val << __ffs(mask) & mask));

	return st_lsm6dsx_shub_write(sensor, addr, &data, sizeof(data));
}