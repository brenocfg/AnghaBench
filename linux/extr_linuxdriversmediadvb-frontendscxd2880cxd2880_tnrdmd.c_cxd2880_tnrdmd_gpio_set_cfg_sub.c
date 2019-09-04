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
typedef  int /*<<< orphan*/  u8 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; int /*<<< orphan*/  diver_sub; } ;
typedef  enum cxd2880_tnrdmd_gpio_mode { ____Placeholder_cxd2880_tnrdmd_gpio_mode } cxd2880_tnrdmd_gpio_mode ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_gpio_set_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxd2880_tnrdmd_gpio_set_cfg_sub(struct cxd2880_tnrdmd *tnr_dmd,
				    u8 id,
				    u8 en,
				    enum cxd2880_tnrdmd_gpio_mode
				    mode, u8 open_drain, u8 invert)
{
	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		return -EINVAL;

	return cxd2880_tnrdmd_gpio_set_cfg(tnr_dmd->diver_sub, id, en, mode,
					   open_drain, invert);
}