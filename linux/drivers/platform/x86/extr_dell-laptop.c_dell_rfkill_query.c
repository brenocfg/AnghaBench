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
struct rfkill {int dummy; } ;
struct calling_interface_buffer {int* output; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASS_INFO ; 
 int /*<<< orphan*/  SELECT_RFKILL ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dell_rfkill_update_hw_state (struct rfkill*,int,int,int) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dell_rfkill_query(struct rfkill *rfkill, void *data)
{
	int radio = ((unsigned long)data & 0xF);
	struct calling_interface_buffer buffer;
	int hwswitch;
	int status;
	int ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	status = buffer.output[1];

	if (ret != 0 || !(status & BIT(0))) {
		return;
	}

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	hwswitch = buffer.output[1];

	if (ret != 0)
		return;

	dell_rfkill_update_hw_state(rfkill, radio, status, hwswitch);
}