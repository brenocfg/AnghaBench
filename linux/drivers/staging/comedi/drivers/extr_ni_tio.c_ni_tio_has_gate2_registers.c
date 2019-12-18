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
struct ni_gpct_device {int variant; } ;

/* Variables and functions */
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 

__attribute__((used)) static bool ni_tio_has_gate2_registers(const struct ni_gpct_device *counter_dev)
{
	switch (counter_dev->variant) {
	case ni_gpct_variant_e_series:
	default:
		return false;
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:
		return true;
	}
}