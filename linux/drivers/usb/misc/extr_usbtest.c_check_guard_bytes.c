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
typedef  scalar_t__ u8 ;
struct usbtest_dev {int dummy; } ;
struct urb {scalar_t__* transfer_buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,unsigned int,scalar_t__,scalar_t__) ; 
 scalar_t__ GUARD_BYTE ; 
 scalar_t__* buffer_offset (scalar_t__*) ; 

__attribute__((used)) static int check_guard_bytes(struct usbtest_dev *tdev, struct urb *urb)
{
	u8 *buf = urb->transfer_buffer;
	u8 *guard = buf - buffer_offset(buf);
	unsigned i;

	for (i = 0; guard < buf; i++, guard++) {
		if (*guard != GUARD_BYTE) {
			ERROR(tdev, "guard byte[%d] %d (not %d)\n",
				i, *guard, GUARD_BYTE);
			return -EINVAL;
		}
	}
	return 0;
}