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
struct seq_file {int dummy; } ;
struct calling_interface_buffer {int* output; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CLASS_INFO ; 
 int /*<<< orphan*/  SELECT_RFKILL ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int dell_debugfs_show(struct seq_file *s, void *data)
{
	struct calling_interface_buffer buffer;
	int hwswitch_state;
	int hwswitch_ret;
	int status;
	int ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	if (ret)
		return ret;
	status = buffer.output[1];

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	hwswitch_ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	if (hwswitch_ret)
		return hwswitch_ret;
	hwswitch_state = buffer.output[1];

	seq_printf(s, "return:\t%d\n", ret);
	seq_printf(s, "status:\t0x%X\n", status);
	seq_printf(s, "Bit 0 : Hardware switch supported:   %lu\n",
		   status & BIT(0));
	seq_printf(s, "Bit 1 : Wifi locator supported:      %lu\n",
		  (status & BIT(1)) >> 1);
	seq_printf(s, "Bit 2 : Wifi is supported:           %lu\n",
		  (status & BIT(2)) >> 2);
	seq_printf(s, "Bit 3 : Bluetooth is supported:      %lu\n",
		  (status & BIT(3)) >> 3);
	seq_printf(s, "Bit 4 : WWAN is supported:           %lu\n",
		  (status & BIT(4)) >> 4);
	seq_printf(s, "Bit 5 : Wireless keyboard supported: %lu\n",
		  (status & BIT(5)) >> 5);
	seq_printf(s, "Bit 6 : UWB supported:               %lu\n",
		  (status & BIT(6)) >> 6);
	seq_printf(s, "Bit 7 : WiGig supported:             %lu\n",
		  (status & BIT(7)) >> 7);
	seq_printf(s, "Bit 8 : Wifi is installed:           %lu\n",
		  (status & BIT(8)) >> 8);
	seq_printf(s, "Bit 9 : Bluetooth is installed:      %lu\n",
		  (status & BIT(9)) >> 9);
	seq_printf(s, "Bit 10: WWAN is installed:           %lu\n",
		  (status & BIT(10)) >> 10);
	seq_printf(s, "Bit 11: UWB installed:               %lu\n",
		  (status & BIT(11)) >> 11);
	seq_printf(s, "Bit 12: WiGig installed:             %lu\n",
		  (status & BIT(12)) >> 12);

	seq_printf(s, "Bit 16: Hardware switch is on:       %lu\n",
		  (status & BIT(16)) >> 16);
	seq_printf(s, "Bit 17: Wifi is blocked:             %lu\n",
		  (status & BIT(17)) >> 17);
	seq_printf(s, "Bit 18: Bluetooth is blocked:        %lu\n",
		  (status & BIT(18)) >> 18);
	seq_printf(s, "Bit 19: WWAN is blocked:             %lu\n",
		  (status & BIT(19)) >> 19);
	seq_printf(s, "Bit 20: UWB is blocked:              %lu\n",
		  (status & BIT(20)) >> 20);
	seq_printf(s, "Bit 21: WiGig is blocked:            %lu\n",
		  (status & BIT(21)) >> 21);

	seq_printf(s, "\nhwswitch_return:\t%d\n", hwswitch_ret);
	seq_printf(s, "hwswitch_state:\t0x%X\n", hwswitch_state);
	seq_printf(s, "Bit 0 : Wifi controlled by switch:      %lu\n",
		   hwswitch_state & BIT(0));
	seq_printf(s, "Bit 1 : Bluetooth controlled by switch: %lu\n",
		   (hwswitch_state & BIT(1)) >> 1);
	seq_printf(s, "Bit 2 : WWAN controlled by switch:      %lu\n",
		   (hwswitch_state & BIT(2)) >> 2);
	seq_printf(s, "Bit 3 : UWB controlled by switch:       %lu\n",
		   (hwswitch_state & BIT(3)) >> 3);
	seq_printf(s, "Bit 4 : WiGig controlled by switch:     %lu\n",
		   (hwswitch_state & BIT(4)) >> 4);
	seq_printf(s, "Bit 7 : Wireless switch config locked:  %lu\n",
		   (hwswitch_state & BIT(7)) >> 7);
	seq_printf(s, "Bit 8 : Wifi locator enabled:           %lu\n",
		   (hwswitch_state & BIT(8)) >> 8);
	seq_printf(s, "Bit 15: Wifi locator setting locked:    %lu\n",
		   (hwswitch_state & BIT(15)) >> 15);

	return 0;
}