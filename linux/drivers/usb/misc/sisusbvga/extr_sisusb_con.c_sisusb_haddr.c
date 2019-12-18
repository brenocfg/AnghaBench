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
struct vc_data {unsigned long vc_origin; } ;
struct sisusb_usb_data {unsigned long scrbuf; unsigned int sisusb_num_columns; unsigned long vrambase; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long sisusb_haddr(const struct sisusb_usb_data *sisusb,
	      const struct vc_data *c, unsigned int x, unsigned int y)
{
	unsigned long offset = c->vc_origin - sisusb->scrbuf;

	/* 2 bytes per each character */
	offset += 2 * (y * sisusb->sisusb_num_columns + x);

	return sisusb->vrambase + offset;
}