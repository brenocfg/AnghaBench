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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct m920x_inits {scalar_t__ address; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int m920x_write (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int m920x_write_seq(struct usb_device *udev, u8 request,
				  struct m920x_inits *seq)
{
	int ret;
	do {
		ret = m920x_write(udev, request, seq->data, seq->address);
		if (ret != 0)
			return ret;

		seq++;
	} while (seq->address);

	return 0;
}