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
struct brcmf_chip {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ CY_CC_43012_CHIP_ID ; 

__attribute__((used)) static bool brcmf_chip_is_ulp(struct brcmf_chip *ci)
{
	if (ci->chip == CY_CC_43012_CHIP_ID)
		return true;
	else
		return false;
}