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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_DATA_VL_ENABLE ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  pio_send_control (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int open_fill_data_vls(struct hfi1_devdata *dd)
{
	if (is_ax(dd))
		return 1;

	pio_send_control(dd, PSC_DATA_VL_ENABLE);

	return 0;
}