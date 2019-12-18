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
struct lp872x_platform_data {int dummy; } ;
struct device {int dummy; } ;
typedef  enum lp872x_id { ____Placeholder_lp872x_id } lp872x_id ;

/* Variables and functions */

__attribute__((used)) static struct lp872x_platform_data
*lp872x_populate_pdata_from_dt(struct device *dev, enum lp872x_id which)
{
	return NULL;
}