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
struct brcmf_sdio {TYPE_1__* ci; } ;
struct TYPE_2__ {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ CY_CC_43012_CHIP_ID ; 

__attribute__((used)) static bool brcmf_sdio_aos_no_decode(struct brcmf_sdio *bus)
{
	if (bus->ci->chip == CY_CC_43012_CHIP_ID)
		return true;
	else
		return false;
}