#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mt9p031 {TYPE_2__* blc_offset; TYPE_4__* blc_auto; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_7__ {scalar_t__ val; } ;
struct TYPE_8__ {TYPE_3__ cur; } ;
struct TYPE_5__ {scalar_t__ val; } ;
struct TYPE_6__ {TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9P031_READ_MODE_2_ROW_BLC ; 
 int /*<<< orphan*/  MT9P031_ROW_BLACK_TARGET ; 
 int mt9p031_set_mode2 (struct mt9p031*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt9p031_write (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9p031_restore_blc(struct mt9p031 *mt9p031)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	int ret;

	if (mt9p031->blc_auto->cur.val != 0) {
		ret = mt9p031_set_mode2(mt9p031, 0,
					MT9P031_READ_MODE_2_ROW_BLC);
		if (ret < 0)
			return ret;
	}

	if (mt9p031->blc_offset->cur.val != 0) {
		ret = mt9p031_write(client, MT9P031_ROW_BLACK_TARGET,
				    mt9p031->blc_offset->cur.val);
		if (ret < 0)
			return ret;
	}

	return 0;
}