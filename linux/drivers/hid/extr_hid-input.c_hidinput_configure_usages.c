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
struct hid_report {int maxfield; TYPE_1__** field; } ;
struct hid_input {int dummy; } ;
struct TYPE_2__ {int maxusage; scalar_t__ usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  hidinput_configure_usage (struct hid_input*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static inline void hidinput_configure_usages(struct hid_input *hidinput,
					     struct hid_report *report)
{
	int i, j;

	for (i = 0; i < report->maxfield; i++)
		for (j = 0; j < report->field[i]->maxusage; j++)
			hidinput_configure_usage(hidinput, report->field[i],
						 report->field[i]->usage + j);
}