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
typedef  unsigned long long u64 ;
struct od_dbs_tuners {int /*<<< orphan*/  powersave_bias; } ;
struct dbs_data {struct od_dbs_tuners* tuners; int /*<<< orphan*/  io_is_busy; scalar_t__ ignore_nice_load; int /*<<< orphan*/  sampling_down_factor; int /*<<< orphan*/  up_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FREQUENCY_UP_THRESHOLD ; 
 int /*<<< orphan*/  DEF_SAMPLING_DOWN_FACTOR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MICRO_FREQUENCY_UP_THRESHOLD ; 
 int /*<<< orphan*/  default_powersave_bias ; 
 int get_cpu () ; 
 unsigned long long get_cpu_idle_time_us (int,int /*<<< orphan*/ *) ; 
 struct od_dbs_tuners* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  should_io_be_busy () ; 

__attribute__((used)) static int od_init(struct dbs_data *dbs_data)
{
	struct od_dbs_tuners *tuners;
	u64 idle_time;
	int cpu;

	tuners = kzalloc(sizeof(*tuners), GFP_KERNEL);
	if (!tuners)
		return -ENOMEM;

	cpu = get_cpu();
	idle_time = get_cpu_idle_time_us(cpu, NULL);
	put_cpu();
	if (idle_time != -1ULL) {
		/* Idle micro accounting is supported. Use finer thresholds */
		dbs_data->up_threshold = MICRO_FREQUENCY_UP_THRESHOLD;
	} else {
		dbs_data->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
	}

	dbs_data->sampling_down_factor = DEF_SAMPLING_DOWN_FACTOR;
	dbs_data->ignore_nice_load = 0;
	tuners->powersave_bias = default_powersave_bias;
	dbs_data->io_is_busy = should_io_be_busy();

	dbs_data->tuners = tuners;
	return 0;
}