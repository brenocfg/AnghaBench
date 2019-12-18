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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * rec_buffer; } ;
struct pcan_usb_pro_msg {int rec_buffer_size; int rec_buffer_len; int /*<<< orphan*/ * rec_ptr; TYPE_1__ u; } ;

/* Variables and functions */
 int PCAN_USBPRO_MSG_HEADER_LEN ; 

__attribute__((used)) static u8 *pcan_msg_init(struct pcan_usb_pro_msg *pm, void *buffer_addr,
			 int buffer_size)
{
	if (buffer_size < PCAN_USBPRO_MSG_HEADER_LEN)
		return NULL;

	pm->u.rec_buffer = (u8 *)buffer_addr;
	pm->rec_buffer_size = pm->rec_buffer_len = buffer_size;
	pm->rec_ptr = pm->u.rec_buffer + PCAN_USBPRO_MSG_HEADER_LEN;

	return pm->rec_ptr;
}