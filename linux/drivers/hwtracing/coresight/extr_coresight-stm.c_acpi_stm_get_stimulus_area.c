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
struct resource {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static inline int acpi_stm_get_stimulus_area(struct device *dev,
					     struct resource *res)
{
	return -ENOENT;
}