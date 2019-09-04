#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int has_dualbuff; int has_cfb64; int has_ctr32; int has_gcm; int has_xts; int has_authenc; int max_burst_size; } ;
struct atmel_aes_dev {int hw_version; int /*<<< orphan*/  dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void atmel_aes_get_cap(struct atmel_aes_dev *dd)
{
	dd->caps.has_dualbuff = 0;
	dd->caps.has_cfb64 = 0;
	dd->caps.has_ctr32 = 0;
	dd->caps.has_gcm = 0;
	dd->caps.has_xts = 0;
	dd->caps.has_authenc = 0;
	dd->caps.max_burst_size = 1;

	/* keep only major version number */
	switch (dd->hw_version & 0xff0) {
	case 0x500:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.has_ctr32 = 1;
		dd->caps.has_gcm = 1;
		dd->caps.has_xts = 1;
		dd->caps.has_authenc = 1;
		dd->caps.max_burst_size = 4;
		break;
	case 0x200:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.has_ctr32 = 1;
		dd->caps.has_gcm = 1;
		dd->caps.max_burst_size = 4;
		break;
	case 0x130:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.max_burst_size = 4;
		break;
	case 0x120:
		break;
	default:
		dev_warn(dd->dev,
				"Unmanaged aes version, set minimum capabilities\n");
		break;
	}
}