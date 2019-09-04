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
struct dfl_feature_platform_data {int /*<<< orphan*/  dev_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATUS_IN_USE ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void dfl_feature_dev_use_end(struct dfl_feature_platform_data *pdata)
{
	clear_bit_unlock(DEV_STATUS_IN_USE, &pdata->dev_status);
}