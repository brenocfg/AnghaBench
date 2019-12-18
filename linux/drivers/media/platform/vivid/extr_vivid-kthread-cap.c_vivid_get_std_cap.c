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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vivid_dev {size_t input; int /*<<< orphan*/ * std_cap; } ;

/* Variables and functions */
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev const*) ; 

__attribute__((used)) static inline v4l2_std_id vivid_get_std_cap(const struct vivid_dev *dev)
{
	if (vivid_is_sdtv_cap(dev))
		return dev->std_cap[dev->input];
	return 0;
}