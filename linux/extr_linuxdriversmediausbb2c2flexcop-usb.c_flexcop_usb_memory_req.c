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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct flexcop_usb {int dummy; } ;
typedef  int flexcop_usb_request_t ;
typedef  scalar_t__ flexcop_usb_mem_page_t ;

/* Variables and functions */
#define  B2C2_USB_FLASH_BLOCK 130 
#define  B2C2_USB_READ_V8_MEM 129 
#define  B2C2_USB_WRITE_V8_MEM 128 
 int EINVAL ; 
 scalar_t__ USB_FLASH_MAX ; 
 scalar_t__ USB_MEM_READ_MAX ; 
 scalar_t__ USB_MEM_WRITE_MAX ; 
 int V8_MEMORY_EXTENDED ; 
 int V8_MEMORY_PAGE_MASK ; 
 int V8_MEMORY_PAGE_SIZE ; 
 scalar_t__ bytes_left_to_read_on_page (int,int) ; 
 int /*<<< orphan*/  deb_info (char*,int) ; 
 int flexcop_usb_v8_memory_req (struct flexcop_usb*,int,scalar_t__,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flexcop_usb_memory_req(struct flexcop_usb *fc_usb,
		flexcop_usb_request_t req, flexcop_usb_mem_page_t page_start,
		u32 addr, int extended, u8 *buf, u32 len)
{
	int i,ret = 0;
	u16 wMax;
	u32 pagechunk = 0;

	switch(req) {
	case B2C2_USB_READ_V8_MEM:
		wMax = USB_MEM_READ_MAX;
		break;
	case B2C2_USB_WRITE_V8_MEM:
		wMax = USB_MEM_WRITE_MAX;
		break;
	case B2C2_USB_FLASH_BLOCK:
		wMax = USB_FLASH_MAX;
		break;
	default:
		return -EINVAL;
		break;
	}
	for (i = 0; i < len;) {
		pagechunk =
			wMax < bytes_left_to_read_on_page(addr, len) ?
				wMax :
				bytes_left_to_read_on_page(addr, len);
		deb_info("%x\n",
			(addr & V8_MEMORY_PAGE_MASK) |
				(V8_MEMORY_EXTENDED*extended));

		ret = flexcop_usb_v8_memory_req(fc_usb, req,
			page_start + (addr / V8_MEMORY_PAGE_SIZE),
			(addr & V8_MEMORY_PAGE_MASK) |
				(V8_MEMORY_EXTENDED*extended),
			&buf[i], pagechunk);

		if (ret < 0)
			return ret;
		addr += pagechunk;
		len -= pagechunk;
	}
	return 0;
}