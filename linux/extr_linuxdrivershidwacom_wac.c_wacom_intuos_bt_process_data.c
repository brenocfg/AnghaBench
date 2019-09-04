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
struct wacom_wac {scalar_t__ pad_input; scalar_t__ pen_input; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_sync (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  wacom_intuos_irq (struct wacom_wac*) ; 

__attribute__((used)) static void wacom_intuos_bt_process_data(struct wacom_wac *wacom,
		unsigned char *data)
{
	memcpy(wacom->data, data, 10);
	wacom_intuos_irq(wacom);

	input_sync(wacom->pen_input);
	if (wacom->pad_input)
		input_sync(wacom->pad_input);
}