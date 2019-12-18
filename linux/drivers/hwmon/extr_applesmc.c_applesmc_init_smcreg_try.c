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
struct applesmc_registers {int init_complete; unsigned int key_count; int fan_count; int has_accelerometer; int has_key_backlight; int num_light_sensors; int /*<<< orphan*/  index_count; scalar_t__ temp_count; scalar_t__ temp_begin; scalar_t__ temp_end; int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_KEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FANS_COUNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIGHT_SENSOR_LEFT_KEY ; 
 int /*<<< orphan*/  LIGHT_SENSOR_RIGHT_KEY ; 
 int /*<<< orphan*/  MOTION_SENSOR_KEY ; 
 int applesmc_get_lower_bound (scalar_t__*,char*) ; 
 int applesmc_has_key (int /*<<< orphan*/ ,int*) ; 
 int applesmc_init_index (struct applesmc_registers*) ; 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int) ; 
 int read_register_count (unsigned int*) ; 
 struct applesmc_registers smcreg ; 

__attribute__((used)) static int applesmc_init_smcreg_try(void)
{
	struct applesmc_registers *s = &smcreg;
	bool left_light_sensor = 0, right_light_sensor = 0;
	unsigned int count;
	u8 tmp[1];
	int ret;

	if (s->init_complete)
		return 0;

	ret = read_register_count(&count);
	if (ret)
		return ret;

	if (s->cache && s->key_count != count) {
		pr_warn("key count changed from %d to %d\n",
			s->key_count, count);
		kfree(s->cache);
		s->cache = NULL;
	}
	s->key_count = count;

	if (!s->cache)
		s->cache = kcalloc(s->key_count, sizeof(*s->cache), GFP_KERNEL);
	if (!s->cache)
		return -ENOMEM;

	ret = applesmc_read_key(FANS_COUNT, tmp, 1);
	if (ret)
		return ret;
	s->fan_count = tmp[0];
	if (s->fan_count > 10)
		s->fan_count = 10;

	ret = applesmc_get_lower_bound(&s->temp_begin, "T");
	if (ret)
		return ret;
	ret = applesmc_get_lower_bound(&s->temp_end, "U");
	if (ret)
		return ret;
	s->temp_count = s->temp_end - s->temp_begin;

	ret = applesmc_init_index(s);
	if (ret)
		return ret;

	ret = applesmc_has_key(LIGHT_SENSOR_LEFT_KEY, &left_light_sensor);
	if (ret)
		return ret;
	ret = applesmc_has_key(LIGHT_SENSOR_RIGHT_KEY, &right_light_sensor);
	if (ret)
		return ret;
	ret = applesmc_has_key(MOTION_SENSOR_KEY, &s->has_accelerometer);
	if (ret)
		return ret;
	ret = applesmc_has_key(BACKLIGHT_KEY, &s->has_key_backlight);
	if (ret)
		return ret;

	s->num_light_sensors = left_light_sensor + right_light_sensor;
	s->init_complete = true;

	pr_info("key=%d fan=%d temp=%d index=%d acc=%d lux=%d kbd=%d\n",
	       s->key_count, s->fan_count, s->temp_count, s->index_count,
	       s->has_accelerometer,
	       s->num_light_sensors,
	       s->has_key_backlight);

	return 0;
}