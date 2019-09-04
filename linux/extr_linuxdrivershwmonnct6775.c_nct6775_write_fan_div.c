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
typedef  int u8 ;
struct nct6775_data {int* fan_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCT6775_REG_FANDIV1 ; 
 int /*<<< orphan*/  NCT6775_REG_FANDIV2 ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nct6775_write_fan_div(struct nct6775_data *data, int nr)
{
	u8 reg;

	switch (nr) {
	case 0:
		reg = (nct6775_read_value(data, NCT6775_REG_FANDIV1) & 0x70)
		    | (data->fan_div[0] & 0x7);
		nct6775_write_value(data, NCT6775_REG_FANDIV1, reg);
		break;
	case 1:
		reg = (nct6775_read_value(data, NCT6775_REG_FANDIV1) & 0x7)
		    | ((data->fan_div[1] << 4) & 0x70);
		nct6775_write_value(data, NCT6775_REG_FANDIV1, reg);
		break;
	case 2:
		reg = (nct6775_read_value(data, NCT6775_REG_FANDIV2) & 0x70)
		    | (data->fan_div[2] & 0x7);
		nct6775_write_value(data, NCT6775_REG_FANDIV2, reg);
		break;
	case 3:
		reg = (nct6775_read_value(data, NCT6775_REG_FANDIV2) & 0x7)
		    | ((data->fan_div[3] << 4) & 0x70);
		nct6775_write_value(data, NCT6775_REG_FANDIV2, reg);
		break;
	}
}