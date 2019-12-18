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
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISCR ; 
 scalar_t__ sisusb_setidxreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
sisusb_initialize(struct sisusb_usb_data *sisusb)
{
	/* Reset cursor and start address */
	if (sisusb_setidxreg(sisusb, SISCR, 0x0c, 0x00))
		return;
	if (sisusb_setidxreg(sisusb, SISCR, 0x0d, 0x00))
		return;
	if (sisusb_setidxreg(sisusb, SISCR, 0x0e, 0x00))
		return;
	sisusb_setidxreg(sisusb, SISCR, 0x0f, 0x00);
}