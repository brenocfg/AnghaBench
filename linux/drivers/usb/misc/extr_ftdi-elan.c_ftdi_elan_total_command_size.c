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
struct usb_ftdi {int command_head; struct u132_command* command; } ;
struct u132_command {scalar_t__ follows; } ;

/* Variables and functions */
 size_t COMMAND_MASK ; 

__attribute__((used)) static int ftdi_elan_total_command_size(struct usb_ftdi *ftdi, int command_size)
{
	int total_size = 0;
	int I = command_size;
	int i = ftdi->command_head;
	while (I-- > 0) {
		struct u132_command *command = &ftdi->command[COMMAND_MASK &
							      i++];
		total_size += 5 + command->follows;
	} return total_size;
}