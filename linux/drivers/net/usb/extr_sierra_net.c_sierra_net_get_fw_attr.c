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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int dummy; } ;
typedef  int /*<<< orphan*/  attrdata ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SWI_USB_REQUEST_GET_FW_ATTR ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usbnet_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sierra_net_get_fw_attr(struct usbnet *dev, u16 *datap)
{
	int result = 0;
	__le16 attrdata;

	result = usbnet_read_cmd(dev,
				/* _u8 vendor specific request */
				SWI_USB_REQUEST_GET_FW_ATTR,
				USB_DIR_IN | USB_TYPE_VENDOR,	/* __u8 request type */
				0x0000,		/* __u16 value not used */
				0x0000,		/* __u16 index  not used */
				&attrdata,	/* char *data */
				sizeof(attrdata)	/* __u16 size */
				);

	if (result < 0)
		return -EIO;

	*datap = le16_to_cpu(attrdata);
	return result;
}