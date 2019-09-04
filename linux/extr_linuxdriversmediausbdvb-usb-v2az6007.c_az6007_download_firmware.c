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
struct firmware {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYPRESS_FX2 ; 
 int cypress_load_firmware (int /*<<< orphan*/ ,struct firmware const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int az6007_download_firmware(struct dvb_usb_device *d,
	const struct firmware *fw)
{
	pr_debug("Loading az6007 firmware\n");

	return cypress_load_firmware(d->udev, fw, CYPRESS_FX2);
}