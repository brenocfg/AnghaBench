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
struct TYPE_2__ {int /*<<< orphan*/  input; } ;
struct wiimote_data {TYPE_1__ extension; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiimod_bboard_in_keys(struct wiimote_data *wdata, const __u8 *keys)
{
	input_report_key(wdata->extension.input, BTN_A,
			 !!(keys[1] & 0x08));
	input_sync(wdata->extension.input);
}