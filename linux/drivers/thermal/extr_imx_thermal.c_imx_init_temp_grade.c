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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct imx_thermal_data {char* temp_grade; int temp_max; int temp_critical; int temp_passive; } ;

/* Variables and functions */
 struct imx_thermal_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void imx_init_temp_grade(struct platform_device *pdev, u32 ocotp_mem0)
{
	struct imx_thermal_data *data = platform_get_drvdata(pdev);

	/* The maximum die temp is specified by the Temperature Grade */
	switch ((ocotp_mem0 >> 6) & 0x3) {
	case 0: /* Commercial (0 to 95 °C) */
		data->temp_grade = "Commercial";
		data->temp_max = 95000;
		break;
	case 1: /* Extended Commercial (-20 °C to 105 °C) */
		data->temp_grade = "Extended Commercial";
		data->temp_max = 105000;
		break;
	case 2: /* Industrial (-40 °C to 105 °C) */
		data->temp_grade = "Industrial";
		data->temp_max = 105000;
		break;
	case 3: /* Automotive (-40 °C to 125 °C) */
		data->temp_grade = "Automotive";
		data->temp_max = 125000;
		break;
	}

	/*
	 * Set the critical trip point at 5 °C under max
	 * Set the passive trip point at 10 °C under max (changeable via sysfs)
	 */
	data->temp_critical = data->temp_max - (1000 * 5);
	data->temp_passive = data->temp_max - (1000 * 10);
}