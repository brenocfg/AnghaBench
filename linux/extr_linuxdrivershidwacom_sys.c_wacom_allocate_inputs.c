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
struct wacom_wac {int /*<<< orphan*/  pad_name; TYPE_2__* pad_input; int /*<<< orphan*/  touch_name; TYPE_1__* touch_input; int /*<<< orphan*/  pen_name; TYPE_3__* pen_input; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* wacom_allocate_input (struct wacom*) ; 

__attribute__((used)) static int wacom_allocate_inputs(struct wacom *wacom)
{
	struct wacom_wac *wacom_wac = &(wacom->wacom_wac);

	wacom_wac->pen_input = wacom_allocate_input(wacom);
	wacom_wac->touch_input = wacom_allocate_input(wacom);
	wacom_wac->pad_input = wacom_allocate_input(wacom);
	if (!wacom_wac->pen_input ||
	    !wacom_wac->touch_input ||
	    !wacom_wac->pad_input)
		return -ENOMEM;

	wacom_wac->pen_input->name = wacom_wac->pen_name;
	wacom_wac->touch_input->name = wacom_wac->touch_name;
	wacom_wac->pad_input->name = wacom_wac->pad_name;

	return 0;
}