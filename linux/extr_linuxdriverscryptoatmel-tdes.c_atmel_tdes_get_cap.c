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
struct TYPE_2__ {int has_dma; int has_cfb_3keys; } ;
struct atmel_tdes_dev {int hw_version; int /*<<< orphan*/  dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void atmel_tdes_get_cap(struct atmel_tdes_dev *dd)
{

	dd->caps.has_dma = 0;
	dd->caps.has_cfb_3keys = 0;

	/* keep only major version number */
	switch (dd->hw_version & 0xf00) {
	case 0x700:
		dd->caps.has_dma = 1;
		dd->caps.has_cfb_3keys = 1;
		break;
	case 0x600:
		break;
	default:
		dev_warn(dd->dev,
				"Unmanaged tdes version, set minimum capabilities\n");
		break;
	}
}