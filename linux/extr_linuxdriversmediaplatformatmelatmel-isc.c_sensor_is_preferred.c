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
struct isc_format {int /*<<< orphan*/  isc_support; scalar_t__ sd_support; } ;

/* Variables and functions */
 scalar_t__ sensor_preferred ; 

__attribute__((used)) static inline bool sensor_is_preferred(const struct isc_format *isc_fmt)
{
	return (sensor_preferred && isc_fmt->sd_support) ||
		!isc_fmt->isc_support;
}