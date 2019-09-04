#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * is_visible; int /*<<< orphan*/  show_label; int /*<<< orphan*/  show_name; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/  read_sensor; } ;
struct abx500_temp {TYPE_3__ ops; int /*<<< orphan*/  monitored_sensors; int /*<<< orphan*/ * gpadc_addr; struct ab8500_temp* plat_data; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tbl_sz; int /*<<< orphan*/  temp_tbl; int /*<<< orphan*/  r_up; int /*<<< orphan*/  vcc; } ;
struct ab8500_temp {TYPE_2__ cfg; int /*<<< orphan*/  power_off_work; int /*<<< orphan*/  btemp; int /*<<< orphan*/  gpadc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_AUX1 ; 
 int /*<<< orphan*/  ADC_AUX2 ; 
 int /*<<< orphan*/  BAT_CTRL ; 
 int /*<<< orphan*/  BTEMP_BALL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_MONITORED_SENSORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PULL_UP_RESISTOR ; 
 int /*<<< orphan*/  THERMAL_VCC ; 
 int /*<<< orphan*/  ab8500_btemp_get () ; 
 int /*<<< orphan*/  ab8500_gpadc_get (char*) ; 
 int /*<<< orphan*/  ab8500_read_sensor ; 
 int /*<<< orphan*/  ab8500_show_label ; 
 int /*<<< orphan*/  ab8500_show_name ; 
 int /*<<< orphan*/  ab8500_temp_irq_handler ; 
 int /*<<< orphan*/  ab8500_temp_tbl_a_size ; 
 int /*<<< orphan*/  ab8500_temp_tbl_a_thermistor ; 
 int /*<<< orphan*/  ab8500_thermal_power_off ; 
 struct ab8500_temp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int abx500_hwmon_init(struct abx500_temp *data)
{
	struct ab8500_temp *ab8500_data;

	ab8500_data = devm_kzalloc(&data->pdev->dev, sizeof(*ab8500_data),
		GFP_KERNEL);
	if (!ab8500_data)
		return -ENOMEM;

	ab8500_data->gpadc = ab8500_gpadc_get("ab8500-gpadc.0");
	if (IS_ERR(ab8500_data->gpadc))
		return PTR_ERR(ab8500_data->gpadc);

	ab8500_data->btemp = ab8500_btemp_get();
	if (IS_ERR(ab8500_data->btemp))
		return PTR_ERR(ab8500_data->btemp);

	INIT_DELAYED_WORK(&ab8500_data->power_off_work,
			  ab8500_thermal_power_off);

	ab8500_data->cfg.vcc = THERMAL_VCC;
	ab8500_data->cfg.r_up = PULL_UP_RESISTOR;
	ab8500_data->cfg.temp_tbl = ab8500_temp_tbl_a_thermistor;
	ab8500_data->cfg.tbl_sz = ab8500_temp_tbl_a_size;

	data->plat_data = ab8500_data;

	/*
	 * ADC_AUX1 and ADC_AUX2, connected to external NTC
	 * BTEMP_BALL and BAT_CTRL, fixed usage
	 */
	data->gpadc_addr[0] = ADC_AUX1;
	data->gpadc_addr[1] = ADC_AUX2;
	data->gpadc_addr[2] = BTEMP_BALL;
	data->gpadc_addr[3] = BAT_CTRL;
	data->monitored_sensors = NUM_MONITORED_SENSORS;

	data->ops.read_sensor = ab8500_read_sensor;
	data->ops.irq_handler = ab8500_temp_irq_handler;
	data->ops.show_name = ab8500_show_name;
	data->ops.show_label = ab8500_show_label;
	data->ops.is_visible = NULL;

	return 0;
}