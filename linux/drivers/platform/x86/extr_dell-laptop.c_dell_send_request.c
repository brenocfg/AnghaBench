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
typedef  void* u16 ;
struct calling_interface_buffer {int /*<<< orphan*/ * output; void* cmd_select; void* cmd_class; } ;

/* Variables and functions */
 int dell_smbios_call (struct calling_interface_buffer*) ; 
 int dell_smbios_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dell_send_request(struct calling_interface_buffer *buffer,
			     u16 class, u16 select)
{
	int ret;

	buffer->cmd_class = class;
	buffer->cmd_select = select;
	ret = dell_smbios_call(buffer);
	if (ret != 0)
		return ret;
	return dell_smbios_error(buffer->output[0]);
}