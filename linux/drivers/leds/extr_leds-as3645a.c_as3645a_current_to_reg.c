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
struct TYPE_2__ {int /*<<< orphan*/  flash_max_ua; int /*<<< orphan*/  assist_max_ua; } ;
struct as3645a {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_FLASH_INTENSITY_MIN ; 
 int /*<<< orphan*/  AS_FLASH_INTENSITY_STEP ; 
 int /*<<< orphan*/  AS_TORCH_INTENSITY_MIN ; 
 int /*<<< orphan*/  AS_TORCH_INTENSITY_STEP ; 
 unsigned int __as3645a_current_to_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int as3645a_current_to_reg(struct as3645a *flash, bool is_flash,
					   unsigned int ua)
{
	if (is_flash)
		return __as3645a_current_to_reg(AS_TORCH_INTENSITY_MIN,
						flash->cfg.assist_max_ua,
						AS_TORCH_INTENSITY_STEP, ua);
	else
		return __as3645a_current_to_reg(AS_FLASH_INTENSITY_MIN,
						flash->cfg.flash_max_ua,
						AS_FLASH_INTENSITY_STEP, ua);
}