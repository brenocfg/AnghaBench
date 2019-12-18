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
struct device {int dummy; } ;
struct adf4350_platform_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static
struct adf4350_platform_data *adf4350_parse_dt(struct device *dev)
{
	return NULL;
}