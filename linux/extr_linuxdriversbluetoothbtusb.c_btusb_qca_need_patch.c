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
typedef  int /*<<< orphan*/  ver ;
struct usb_device {int dummy; } ;
struct qca_version {int /*<<< orphan*/  rom_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA_GET_TARGET_VERSION ; 
 scalar_t__ btusb_qca_send_vendor_req (struct usb_device*,int /*<<< orphan*/ ,struct qca_version*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool btusb_qca_need_patch(struct usb_device *udev)
{
	struct qca_version ver;

	if (btusb_qca_send_vendor_req(udev, QCA_GET_TARGET_VERSION, &ver,
				      sizeof(ver)) < 0)
		return false;
	/* only low ROM versions need patches */
	return !(le32_to_cpu(ver.rom_version) & ~0xffffU);
}