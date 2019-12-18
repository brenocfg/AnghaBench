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
struct TYPE_2__ {scalar_t__* rec_cnt; } ;
struct pcan_usb_pro_msg {TYPE_1__ u; int /*<<< orphan*/  rec_buffer_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_USBPRO_MSG_HEADER_LEN ; 
 int /*<<< orphan*/ * pcan_msg_init (struct pcan_usb_pro_msg*,void*,int) ; 

__attribute__((used)) static u8 *pcan_msg_init_empty(struct pcan_usb_pro_msg *pm,
			       void *buffer_addr, int buffer_size)
{
	u8 *pr = pcan_msg_init(pm, buffer_addr, buffer_size);

	if (pr) {
		pm->rec_buffer_len = PCAN_USBPRO_MSG_HEADER_LEN;
		*pm->u.rec_cnt = 0;
	}
	return pr;
}