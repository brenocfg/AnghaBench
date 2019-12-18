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
struct mv_udc {scalar_t__ clock_gating; } ;

/* Variables and functions */
 int /*<<< orphan*/  mv_udc_disable_internal (struct mv_udc*) ; 

__attribute__((used)) static void mv_udc_disable(struct mv_udc *udc)
{
	if (udc->clock_gating)
		mv_udc_disable_internal(udc);
}