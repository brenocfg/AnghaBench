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
struct hid_field {int logical_maximum; int logical_minimum; } ;

/* Variables and functions */

__attribute__((used)) static int pidff_rescale(int i, int max, struct hid_field *field)
{
	return i * (field->logical_maximum - field->logical_minimum) / max +
	    field->logical_minimum;
}