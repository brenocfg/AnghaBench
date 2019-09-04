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
struct menelaus_vtg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int menelaus_get_vtg_value (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menelaus_set_voltage (struct menelaus_vtg const*,unsigned int,int,int) ; 
 struct menelaus_vtg vdcdc2_vtg ; 
 struct menelaus_vtg vdcdc3_vtg ; 
 int /*<<< orphan*/  vdcdc_values ; 

int menelaus_set_vdcdc(int dcdc, unsigned int mV)
{
	const struct menelaus_vtg *vtg;
	int val;

	if (dcdc != 2 && dcdc != 3)
		return -EINVAL;
	if (dcdc == 2)
		vtg = &vdcdc2_vtg;
	else
		vtg = &vdcdc3_vtg;

	if (mV == 0)
		return menelaus_set_voltage(vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vdcdc_values,
				     ARRAY_SIZE(vdcdc_values));
	if (val < 0)
		return -EINVAL;
	return menelaus_set_voltage(vtg, mV, val, 0x03);
}