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
struct usb_ftdi {int command_next; int command_head; int expected; int /*<<< orphan*/  u132_lock; scalar_t__ ed_found; scalar_t__ received; struct u132_command* command; struct u132_target* target; } ;
struct u132_target {int abandoning; int active; } ;
struct u132_command {int header; int length; int address; int width; scalar_t__ value; scalar_t__* buffer; scalar_t__ follows; } ;

/* Variables and functions */
 size_t COMMAND_MASK ; 
 int COMMAND_SIZE ; 
 int /*<<< orphan*/  ftdi_elan_kick_command_queue (struct usb_ftdi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftdi_elan_flush_targets(struct usb_ftdi *ftdi)
{
	int ed_number = 4;
	mutex_lock(&ftdi->u132_lock);
	while (ed_number-- > 0) {
		struct u132_target *target = &ftdi->target[ed_number];
		target->abandoning = 1;
	wait_1:if (target->active == 1) {
			int command_size = ftdi->command_next -
				ftdi->command_head;
			if (command_size < COMMAND_SIZE) {
				struct u132_command *command = &ftdi->command[
					COMMAND_MASK & ftdi->command_next];
				command->header = 0x80 | (ed_number << 5) | 0x4;
				command->length = 0x00;
				command->address = 0x00;
				command->width = 0x00;
				command->follows = 0;
				command->value = 0;
				command->buffer = &command->value;
				ftdi->command_next += 1;
				ftdi_elan_kick_command_queue(ftdi);
			} else {
				mutex_unlock(&ftdi->u132_lock);
				msleep(100);
				mutex_lock(&ftdi->u132_lock);
				goto wait_1;
			}
		}
	wait_2:if (target->active == 1) {
			int command_size = ftdi->command_next -
				ftdi->command_head;
			if (command_size < COMMAND_SIZE) {
				struct u132_command *command = &ftdi->command[
					COMMAND_MASK & ftdi->command_next];
				command->header = 0x90 | (ed_number << 5);
				command->length = 0x00;
				command->address = 0x00;
				command->width = 0x00;
				command->follows = 0;
				command->value = 0;
				command->buffer = &command->value;
				ftdi->command_next += 1;
				ftdi_elan_kick_command_queue(ftdi);
			} else {
				mutex_unlock(&ftdi->u132_lock);
				msleep(100);
				mutex_lock(&ftdi->u132_lock);
				goto wait_2;
			}
		}
	}
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	mutex_unlock(&ftdi->u132_lock);
}