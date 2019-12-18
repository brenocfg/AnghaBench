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
struct nct6683_data {int* temp_index; int customer_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NCT6683_CUSTOMER_ID_INTEL 129 
#define  NCT6683_CUSTOMER_ID_MITAC 128 
 int NCT6683_REG_INTEL_TEMP_CRIT (int) ; 
 int NCT6683_REG_INTEL_TEMP_MAX (int) ; 
 int NCT6683_REG_MON_HIGH (int) ; 
 int NCT6683_REG_MON_LOW (int) ; 
 int NCT6683_REG_TEMP_HYST (int) ; 
 int NCT6683_REG_TEMP_MAX (int) ; 

__attribute__((used)) static int get_temp_reg(struct nct6683_data *data, int nr, int index)
{
	int ch = data->temp_index[index];
	int reg = -EINVAL;

	switch (data->customer_id) {
	case NCT6683_CUSTOMER_ID_INTEL:
		switch (nr) {
		default:
		case 1:	/* max */
			reg = NCT6683_REG_INTEL_TEMP_MAX(ch);
			break;
		case 3:	/* crit */
			reg = NCT6683_REG_INTEL_TEMP_CRIT(ch);
			break;
		}
		break;
	case NCT6683_CUSTOMER_ID_MITAC:
	default:
		switch (nr) {
		default:
		case 0:	/* min */
			reg = NCT6683_REG_MON_LOW(ch);
			break;
		case 1:	/* max */
			reg = NCT6683_REG_TEMP_MAX(ch);
			break;
		case 2:	/* hyst */
			reg = NCT6683_REG_TEMP_HYST(ch);
			break;
		case 3:	/* crit */
			reg = NCT6683_REG_MON_HIGH(ch);
			break;
		}
		break;
	}
	return reg;
}