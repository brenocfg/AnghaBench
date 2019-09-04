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
typedef  int uint8_t ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct auo_point_t {int coord_x; int coord_y; int orientation; int /*<<< orphan*/  area_minor; int /*<<< orphan*/  area_major; } ;
struct auo_pixcir_ts_platdata {int x_max; int y_max; } ;
struct auo_pixcir_ts {struct auo_pixcir_ts_platdata* pdata; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUO_PIXCIR_REG_TOUCHAREA_X1 ; 
 int /*<<< orphan*/  AUO_PIXCIR_REG_X1_LSB ; 
 int AUO_PIXCIR_REPORT_POINTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static int auo_pixcir_collect_data(struct auo_pixcir_ts *ts,
				   struct auo_point_t *point)
{
	struct i2c_client *client = ts->client;
	const struct auo_pixcir_ts_platdata *pdata = ts->pdata;
	uint8_t raw_coord[8];
	uint8_t raw_area[4];
	int i, ret;

	/* touch coordinates */
	ret = i2c_smbus_read_i2c_block_data(client, AUO_PIXCIR_REG_X1_LSB,
					    8, raw_coord);
	if (ret < 0) {
		dev_err(&client->dev, "failed to read coordinate, %d\n", ret);
		return ret;
	}

	/* touch area */
	ret = i2c_smbus_read_i2c_block_data(client, AUO_PIXCIR_REG_TOUCHAREA_X1,
					    4, raw_area);
	if (ret < 0) {
		dev_err(&client->dev, "could not read touch area, %d\n", ret);
		return ret;
	}

	for (i = 0; i < AUO_PIXCIR_REPORT_POINTS; i++) {
		point[i].coord_x =
			raw_coord[4 * i + 1] << 8 | raw_coord[4 * i];
		point[i].coord_y =
			raw_coord[4 * i + 3] << 8 | raw_coord[4 * i + 2];

		if (point[i].coord_x > pdata->x_max ||
		    point[i].coord_y > pdata->y_max) {
			dev_warn(&client->dev, "coordinates (%d,%d) invalid\n",
				point[i].coord_x, point[i].coord_y);
			point[i].coord_x = point[i].coord_y = 0;
		}

		/* determine touch major, minor and orientation */
		point[i].area_major = max(raw_area[2 * i], raw_area[2 * i + 1]);
		point[i].area_minor = min(raw_area[2 * i], raw_area[2 * i + 1]);
		point[i].orientation = raw_area[2 * i] > raw_area[2 * i + 1];
	}

	return 0;
}