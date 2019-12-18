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
struct intel_pinctrl {int dummy; } ;

/* Variables and functions */
 scalar_t__ intel_pad_is_unlocked (struct intel_pinctrl*,unsigned int) ; 
 scalar_t__ intel_pad_owned_by_host (struct intel_pinctrl*,unsigned int) ; 

__attribute__((used)) static bool intel_pad_usable(struct intel_pinctrl *pctrl, unsigned int pin)
{
	return intel_pad_owned_by_host(pctrl, pin) && intel_pad_is_unlocked(pctrl, pin);
}