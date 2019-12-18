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
struct ni_gpct_device {scalar_t__ variant; } ;

/* Variables and functions */
 scalar_t__ ni_gpct_variant_e_series ; 

__attribute__((used)) static inline bool
ni_tio_counting_mode_registers_present(const struct ni_gpct_device *counter_dev)
{
	/* m series and 660x variants have counting mode registers */
	return counter_dev->variant != ni_gpct_variant_e_series;
}