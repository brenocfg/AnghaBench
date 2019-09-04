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
struct pixcir_i2c_ts_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pixcir_parse_dt(struct device *dev,
			   struct pixcir_i2c_ts_data *tsdata)
{
	return -EINVAL;
}