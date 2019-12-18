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
struct asus_wmi {int agfn_pwm; } ;
struct TYPE_2__ {int len; scalar_t__ err; int /*<<< orphan*/  sfun; int /*<<< orphan*/  mfun; } ;
struct agfn_fan_args {int fan; int speed; TYPE_1__ agfn; } ;
struct acpi_buffer {struct agfn_fan_args* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_FAN_MFUN ; 
 int /*<<< orphan*/  ASUS_FAN_SFUN_WRITE ; 
 int EINVAL ; 
 int ENXIO ; 
 int asus_wmi_evaluate_method_agfn (struct acpi_buffer) ; 

__attribute__((used)) static int asus_agfn_fan_speed_write(struct asus_wmi *asus, int fan,
				     int *speed)
{
	struct agfn_fan_args args = {
		.agfn.len = sizeof(args),
		.agfn.mfun = ASUS_FAN_MFUN,
		.agfn.sfun = ASUS_FAN_SFUN_WRITE,
		.fan = fan,
		.speed = speed ?  *speed : 0,
	};
	struct acpi_buffer input = { (acpi_size) sizeof(args), &args };
	int status;

	/* 1: for setting 1st fan's speed 0: setting auto mode */
	if (fan != 1 && fan != 0)
		return -EINVAL;

	status = asus_wmi_evaluate_method_agfn(input);

	if (status || args.agfn.err)
		return -ENXIO;

	if (speed && fan == 1)
		asus->agfn_pwm = *speed;

	return 0;
}