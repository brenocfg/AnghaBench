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
struct memac_cfg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool is_init_done(struct memac_cfg *memac_drv_params)
{
	/* Checks if mEMAC driver parameters were initialized */
	if (!memac_drv_params)
		return true;

	return false;
}