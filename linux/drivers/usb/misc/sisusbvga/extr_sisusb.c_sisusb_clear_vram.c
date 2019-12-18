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
typedef  scalar_t__ u32 ;
struct sisusb_usb_data {scalar_t__ vrambase; scalar_t__ vramsize; int /*<<< orphan*/  obufsize; int /*<<< orphan*/ * obuf; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sisusb_alloc_outbuf (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_free_outbuf (struct sisusb_usb_data*,int) ; 
 int sisusb_write_mem_bulk (struct sisusb_usb_data*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sisusb_clear_vram(struct sisusb_usb_data *sisusb,
		u32 address, int length)
{
	int ret, i;
	ssize_t j;

	if (address < sisusb->vrambase)
		return 1;

	if (address >= sisusb->vrambase + sisusb->vramsize)
		return 1;

	if (address + length > sisusb->vrambase + sisusb->vramsize)
		length = sisusb->vrambase + sisusb->vramsize - address;

	if (length <= 0)
		return 0;

	/* allocate free buffer/urb and clear the buffer */
	i = sisusb_alloc_outbuf(sisusb);
	if (i < 0)
		return -EBUSY;

	memset(sisusb->obuf[i], 0, sisusb->obufsize);

	/* We can write a length > buffer size here. The buffer
	 * data will simply be re-used (like a ring-buffer).
	 */
	ret = sisusb_write_mem_bulk(sisusb, address, NULL, length, NULL, i, &j);

	/* Free the buffer/urb */
	sisusb_free_outbuf(sisusb, i);

	return ret;
}