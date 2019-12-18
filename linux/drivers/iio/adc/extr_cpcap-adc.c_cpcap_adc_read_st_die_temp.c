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
struct cpcap_adc {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int cpcap_adc_read_st_die_temp(struct cpcap_adc *ddata,
				      int addr, int *val)
{
	int error;

	error = regmap_read(ddata->reg, addr, val);
	if (error)
		return error;

	*val -= 282;
	*val *= 114;
	*val += 25000;

	return 0;
}