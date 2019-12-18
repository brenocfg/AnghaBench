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
struct uclogic_params {scalar_t__ pen_unused; } ;
struct uclogic_drvdata {struct uclogic_params params; } ;
struct hid_usage {int dummy; } ;
struct hid_input {int dummy; } ;
struct hid_field {scalar_t__ application; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HID_DG_PEN ; 
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int uclogic_input_mapping(struct hid_device *hdev,
				 struct hid_input *hi,
				 struct hid_field *field,
				 struct hid_usage *usage,
				 unsigned long **bit,
				 int *max)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	struct uclogic_params *params = &drvdata->params;

	/* discard the unused pen interface */
	if (params->pen_unused && (field->application == HID_DG_PEN))
		return -1;

	/* let hid-core decide what to do */
	return 0;
}