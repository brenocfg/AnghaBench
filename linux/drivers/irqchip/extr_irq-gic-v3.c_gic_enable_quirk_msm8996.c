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
struct gic_chip_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_WORKAROUND_GICR_WAKER_MSM8996 ; 

__attribute__((used)) static bool gic_enable_quirk_msm8996(void *data)
{
	struct gic_chip_data *d = data;

	d->flags |= FLAGS_WORKAROUND_GICR_WAKER_MSM8996;

	return true;
}