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
struct ms_data {unsigned long quirks; } ;
struct hid_usage {int /*<<< orphan*/  code; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 unsigned long MS_DUPLICATE_USAGES ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct ms_data* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int ms_input_mapped(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	struct ms_data *ms = hid_get_drvdata(hdev);
	unsigned long quirks = ms->quirks;

	if (quirks & MS_DUPLICATE_USAGES)
		clear_bit(usage->code, *bit);

	return 0;
}