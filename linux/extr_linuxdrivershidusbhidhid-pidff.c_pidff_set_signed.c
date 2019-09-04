#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pidff_usage {void** value; TYPE_1__* field; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_3__ {scalar_t__ logical_minimum; } ;

/* Variables and functions */
 void* pidff_rescale (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 void* pidff_rescale_signed (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void pidff_set_signed(struct pidff_usage *usage, s16 value)
{
	if (usage->field->logical_minimum < 0)
		usage->value[0] = pidff_rescale_signed(value, usage->field);
	else {
		if (value < 0)
			usage->value[0] =
			    pidff_rescale(-value, 0x8000, usage->field);
		else
			usage->value[0] =
			    pidff_rescale(value, 0x7fff, usage->field);
	}
	pr_debug("calculated from %d to %d\n", value, usage->value[0]);
}