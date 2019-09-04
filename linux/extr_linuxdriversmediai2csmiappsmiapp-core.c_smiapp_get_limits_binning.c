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
typedef  size_t u32 ;
struct smiapp_sensor {int /*<<< orphan*/ * limits; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  what; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (size_t const*) ; 
 int /*<<< orphan*/  SMIAPP_BINNING_CAPABILITY_NO ; 
 size_t SMIAPP_LIMIT_BINNING_CAPABILITY ; 
#define  SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MAX_MARGIN 141 
#define  SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MAX_MARGIN_BIN 140 
#define  SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MIN 139 
#define  SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MIN_BIN 138 
#define  SMIAPP_LIMIT_MAX_FRAME_LENGTH_LINES 137 
#define  SMIAPP_LIMIT_MAX_FRAME_LENGTH_LINES_BIN 136 
#define  SMIAPP_LIMIT_MAX_LINE_LENGTH_PCK 135 
#define  SMIAPP_LIMIT_MAX_LINE_LENGTH_PCK_BIN 134 
#define  SMIAPP_LIMIT_MIN_FRAME_LENGTH_LINES 133 
#define  SMIAPP_LIMIT_MIN_FRAME_LENGTH_LINES_BIN 132 
#define  SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK 131 
#define  SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK_BIN 130 
#define  SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK 129 
#define  SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK_BIN 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smiapp_get_limits (struct smiapp_sensor*,size_t const*,unsigned int) ; 
 TYPE_2__* smiapp_reg_limits ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_get_limits_binning(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	static u32 const limits[] = {
		SMIAPP_LIMIT_MIN_FRAME_LENGTH_LINES_BIN,
		SMIAPP_LIMIT_MAX_FRAME_LENGTH_LINES_BIN,
		SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK_BIN,
		SMIAPP_LIMIT_MAX_LINE_LENGTH_PCK_BIN,
		SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK_BIN,
		SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MIN_BIN,
		SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MAX_MARGIN_BIN,
	};
	static u32 const limits_replace[] = {
		SMIAPP_LIMIT_MIN_FRAME_LENGTH_LINES,
		SMIAPP_LIMIT_MAX_FRAME_LENGTH_LINES,
		SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK,
		SMIAPP_LIMIT_MAX_LINE_LENGTH_PCK,
		SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK,
		SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MIN,
		SMIAPP_LIMIT_FINE_INTEGRATION_TIME_MAX_MARGIN,
	};
	unsigned int i;
	int rval;

	if (sensor->limits[SMIAPP_LIMIT_BINNING_CAPABILITY] ==
	    SMIAPP_BINNING_CAPABILITY_NO) {
		for (i = 0; i < ARRAY_SIZE(limits); i++)
			sensor->limits[limits[i]] =
				sensor->limits[limits_replace[i]];

		return 0;
	}

	rval = smiapp_get_limits(sensor, limits, ARRAY_SIZE(limits));
	if (rval < 0)
		return rval;

	/*
	 * Sanity check whether the binning limits are valid. If not,
	 * use the non-binning ones.
	 */
	if (sensor->limits[SMIAPP_LIMIT_MIN_FRAME_LENGTH_LINES_BIN]
	    && sensor->limits[SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK_BIN]
	    && sensor->limits[SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK_BIN])
		return 0;

	for (i = 0; i < ARRAY_SIZE(limits); i++) {
		dev_dbg(&client->dev,
			"replace limit 0x%8.8x \"%s\" = %d, 0x%x\n",
			smiapp_reg_limits[limits[i]].addr,
			smiapp_reg_limits[limits[i]].what,
			sensor->limits[limits_replace[i]],
			sensor->limits[limits_replace[i]]);
		sensor->limits[limits[i]] =
			sensor->limits[limits_replace[i]];
	}

	return 0;
}