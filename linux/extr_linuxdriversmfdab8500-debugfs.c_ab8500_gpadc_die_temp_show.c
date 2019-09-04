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
 int /*<<< orphan*/  DIE_TEMP ; 
 int ab8500_gpadc_ad_to_voltage (struct ab8500_gpadc*,int /*<<< orphan*/ ,int) ; 
 struct ab8500_gpadc* ab8500_gpadc_get (char*) ; 
 int ab8500_gpadc_read_raw (struct ab8500_gpadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avg_sample ; 
 int /*<<< orphan*/  conv_type ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int /*<<< orphan*/  trig_edge ; 
 int /*<<< orphan*/  trig_timer ; 

__attribute__((used)) static int ab8500_gpadc_die_temp_show(struct seq_file *s, void *p)
{
	int die_temp_raw;
	int die_temp_convert;
	struct ab8500_gpadc *gpadc;

	gpadc = ab8500_gpadc_get("ab8500-gpadc.0");
	die_temp_raw = ab8500_gpadc_read_raw(gpadc, DIE_TEMP,
		avg_sample, trig_edge, trig_timer, conv_type);
	die_temp_convert = ab8500_gpadc_ad_to_voltage(gpadc, DIE_TEMP,
		die_temp_raw);

	seq_printf(s, "%d,0x%X\n", die_temp_convert, die_temp_raw);

	return 0;
}