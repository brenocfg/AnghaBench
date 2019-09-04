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
struct mt9m032 {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M032_READ_MODE2 ; 
 int MT9M032_READ_MODE2_HFLIP_SHIFT ; 
 int MT9M032_READ_MODE2_ROW_BLC ; 
 int MT9M032_READ_MODE2_VFLIP_SHIFT ; 
 int mt9m032_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_read_mode2(struct mt9m032 *sensor, bool vflip, bool hflip)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	int reg_val = (vflip << MT9M032_READ_MODE2_VFLIP_SHIFT)
		    | (hflip << MT9M032_READ_MODE2_HFLIP_SHIFT)
		    | MT9M032_READ_MODE2_ROW_BLC
		    | 0x0007;

	return mt9m032_write(client, MT9M032_READ_MODE2, reg_val);
}