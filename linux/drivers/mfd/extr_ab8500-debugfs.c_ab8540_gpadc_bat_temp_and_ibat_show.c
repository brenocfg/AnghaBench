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
struct seq_file {int dummy; } ;
struct ab8500_gpadc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_TEMP_AND_IBAT ; 
 int /*<<< orphan*/  BTEMP_BALL ; 
 int /*<<< orphan*/  IBAT_VIRTUAL_CHANNEL ; 
 int ab8500_gpadc_ad_to_voltage (struct ab8500_gpadc*,int /*<<< orphan*/ ,int) ; 
 int ab8500_gpadc_double_read_raw (struct ab8500_gpadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct ab8500_gpadc* ab8500_gpadc_get (char*) ; 
 int /*<<< orphan*/  avg_sample ; 
 int /*<<< orphan*/  conv_type ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  trig_edge ; 
 int /*<<< orphan*/  trig_timer ; 

__attribute__((used)) static int ab8540_gpadc_bat_temp_and_ibat_show(struct seq_file *s, void *p)
{
	int bat_temp_raw;
	int bat_temp_convert;
	int ibat_raw;
	int ibat_convert;
	struct ab8500_gpadc *gpadc;

	gpadc = ab8500_gpadc_get("ab8500-gpadc.0");
	bat_temp_raw = ab8500_gpadc_double_read_raw(gpadc, BAT_TEMP_AND_IBAT,
		avg_sample, trig_edge, trig_timer, conv_type, &ibat_raw);
	bat_temp_convert = ab8500_gpadc_ad_to_voltage(gpadc, BTEMP_BALL,
		bat_temp_raw);
	ibat_convert = ab8500_gpadc_ad_to_voltage(gpadc, IBAT_VIRTUAL_CHANNEL,
		ibat_raw);

	seq_printf(s,
		   "%d,0x%X\n"
		   "%d,0x%X\n",
		   bat_temp_convert, bat_temp_raw,
		   ibat_convert, ibat_raw);

	return 0;
}