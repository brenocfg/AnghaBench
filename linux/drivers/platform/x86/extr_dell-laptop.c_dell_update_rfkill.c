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
struct work_struct {int dummy; } ;
struct calling_interface_buffer {int* output; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASS_INFO ; 
 int /*<<< orphan*/  SELECT_RFKILL ; 
 scalar_t__ bluetooth_rfkill ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dell_rfkill_update_hw_state (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  dell_rfkill_update_sw_state (scalar_t__,int,int) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wifi_rfkill ; 
 scalar_t__ wwan_rfkill ; 

__attribute__((used)) static void dell_update_rfkill(struct work_struct *ignored)
{
	struct calling_interface_buffer buffer;
	int hwswitch = 0;
	int status;
	int ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	status = buffer.output[1];

	if (ret != 0)
		return;

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);

	if (ret == 0 && (status & BIT(0)))
		hwswitch = buffer.output[1];

	if (wifi_rfkill) {
		dell_rfkill_update_hw_state(wifi_rfkill, 1, status, hwswitch);
		dell_rfkill_update_sw_state(wifi_rfkill, 1, status);
	}
	if (bluetooth_rfkill) {
		dell_rfkill_update_hw_state(bluetooth_rfkill, 2, status,
					    hwswitch);
		dell_rfkill_update_sw_state(bluetooth_rfkill, 2, status);
	}
	if (wwan_rfkill) {
		dell_rfkill_update_hw_state(wwan_rfkill, 3, status, hwswitch);
		dell_rfkill_update_sw_state(wwan_rfkill, 3, status);
	}
}