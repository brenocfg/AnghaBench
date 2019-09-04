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
struct mmc35240_data {size_t res; int* axis_coef; int* axis_scale; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int* sens; int nfo; } ;

/* Variables and functions */
#define  AXIS_X 130 
#define  AXIS_Y 129 
#define  AXIS_Z 128 
 int EINVAL ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* mmc35240_props_table ; 

__attribute__((used)) static int mmc35240_raw_to_mgauss(struct mmc35240_data *data, int index,
				  __le16 buf[], int *val)
{
	int raw[3];
	int sens[3];
	int nfo;

	raw[AXIS_X] = le16_to_cpu(buf[AXIS_X]);
	raw[AXIS_Y] = le16_to_cpu(buf[AXIS_Y]);
	raw[AXIS_Z] = le16_to_cpu(buf[AXIS_Z]);

	sens[AXIS_X] = mmc35240_props_table[data->res].sens[AXIS_X];
	sens[AXIS_Y] = mmc35240_props_table[data->res].sens[AXIS_Y];
	sens[AXIS_Z] = mmc35240_props_table[data->res].sens[AXIS_Z];

	nfo = mmc35240_props_table[data->res].nfo;

	switch (index) {
	case AXIS_X:
		*val = (raw[AXIS_X] - nfo) * 1000 / sens[AXIS_X];
		break;
	case AXIS_Y:
		*val = (raw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] -
			(raw[AXIS_Z] - nfo)  * 1000 / sens[AXIS_Z];
		break;
	case AXIS_Z:
		*val = (raw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] +
			(raw[AXIS_Z] - nfo) * 1000 / sens[AXIS_Z];
		break;
	default:
		return -EINVAL;
	}
	/* apply OTP compensation */
	*val = (*val) * data->axis_coef[index] / data->axis_scale[index];

	return 0;
}