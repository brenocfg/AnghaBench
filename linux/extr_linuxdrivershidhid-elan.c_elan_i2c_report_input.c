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
struct input_dev {int dummy; } ;
struct elan_drvdata {struct input_dev* input; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  ELAN_FINGER_DATA_LEN ; 
 int ELAN_MAX_FINGERS ; 
 int /*<<< orphan*/  elan_report_mt_slot (struct elan_drvdata*,int*,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void elan_i2c_report_input(struct elan_drvdata *drvdata, u8 *data)
{
	struct input_dev *input = drvdata->input;
	u8 *finger_data;
	int i;

	/*
	 * Elan MT touchpads in i2c mode send finger data in the same format
	 * as in USB mode, but then with all fingers in a single packet.
	 *
	 * packet structure for ELAN_MT_I2C:
	 *
	 * byte     1: 1   0   0   1   1   1   0   1   // 0x5d
	 * byte     2: f5  f4  f3  f2  f1  0   0   L
	 * byte     3: x12 x11 x10 x9  0?  y11 y10 y9
	 * byte     4: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte     5: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte     6: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte     7: p8  p7  p6  p5  p4  p3  p2  p1
	 * byte  8-12: Same as byte 3-7 for second finger down
	 * byte 13-17: Same as byte 3-7 for third finger down
	 * byte 18-22: Same as byte 3-7 for fourth finger down
	 * byte 23-27: Same as byte 3-7 for fifth finger down
	 */

	finger_data = data + 2;
	for (i = 0; i < ELAN_MAX_FINGERS; i++) {
		if (data[1] & BIT(i + 3)) {
			elan_report_mt_slot(drvdata, finger_data, i);
			finger_data += ELAN_FINGER_DATA_LEN;
		} else {
			elan_report_mt_slot(drvdata, NULL, i);
		}
	}

	input_report_key(input, BTN_LEFT, data[1] & 0x01);
	input_mt_sync_frame(input);
	input_sync(input);
}