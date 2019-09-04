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
struct dfl_feature_platform_data {void* private; } ;

/* Variables and functions */

__attribute__((used)) static inline
void dfl_fpga_pdata_set_private(struct dfl_feature_platform_data *pdata,
				void *private)
{
	pdata->private = private;
}