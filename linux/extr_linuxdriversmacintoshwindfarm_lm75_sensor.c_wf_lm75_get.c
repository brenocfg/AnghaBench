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
struct wf_sensor {int /*<<< orphan*/  name; } ;
struct wf_lm75_sensor {int inited; int /*<<< orphan*/ * i2c; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_smbus_read_word_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct wf_lm75_sensor* wf_to_lm75 (struct wf_sensor*) ; 

__attribute__((used)) static int wf_lm75_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_lm75_sensor *lm = wf_to_lm75(sr);
	s32 data;

	if (lm->i2c == NULL)
		return -ENODEV;

	/* Init chip if necessary */
	if (!lm->inited) {
		u8 cfg_new, cfg = (u8)i2c_smbus_read_byte_data(lm->i2c, 1);

		DBG("wf_lm75: Initializing %s, cfg was: %02x\n",
		    sr->name, cfg);

		/* clear shutdown bit, keep other settings as left by
		 * the firmware for now
		 */
		cfg_new = cfg & ~0x01;
		i2c_smbus_write_byte_data(lm->i2c, 1, cfg_new);
		lm->inited = 1;

		/* If we just powered it up, let's wait 200 ms */
		msleep(200);
	}

	/* Read temperature register */
	data = (s32)le16_to_cpu(i2c_smbus_read_word_data(lm->i2c, 0));
	data <<= 8;
	*value = data;

	return 0;
}