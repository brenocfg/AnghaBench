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
struct hid_usage {scalar_t__ type; } ;
struct hid_input {TYPE_1__* input; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 scalar_t__ EV_KEY ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icade_input_mapped(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if (usage->type == EV_KEY)
		set_bit(usage->type, hi->input->evbit);

	return -1;
}