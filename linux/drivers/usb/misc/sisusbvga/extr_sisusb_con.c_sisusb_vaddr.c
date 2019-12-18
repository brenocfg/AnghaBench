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
typedef  void u16 ;
struct vc_data {scalar_t__ vc_origin; } ;
struct sisusb_usb_data {unsigned int sisusb_num_columns; } ;

/* Variables and functions */

__attribute__((used)) static inline void *sisusb_vaddr(const struct sisusb_usb_data *sisusb,
		const struct vc_data *c, unsigned int x, unsigned int y)
{
	return (u16 *)c->vc_origin + y * sisusb->sisusb_num_columns + x;
}