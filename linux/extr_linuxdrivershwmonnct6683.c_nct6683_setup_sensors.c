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
typedef  size_t u8 ;
struct nct6683_data {size_t temp_num; size_t in_num; int* temp_index; size_t* temp_src; int* in_index; size_t* in_src; } ;

/* Variables and functions */
 size_t MON_VOLTAGE_START ; 
 int NCT6683_NUM_REG_MON ; 
 int /*<<< orphan*/  NCT6683_REG_MON_CFG (int) ; 
 size_t NUM_MON_LABELS ; 
 int /*<<< orphan*/ ** nct6683_mon_label ; 
 int nct6683_read (struct nct6683_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nct6683_setup_sensors(struct nct6683_data *data)
{
	u8 reg;
	int i;

	data->temp_num = 0;
	data->in_num = 0;
	for (i = 0; i < NCT6683_NUM_REG_MON; i++) {
		reg = nct6683_read(data, NCT6683_REG_MON_CFG(i)) & 0x7f;
		/* Ignore invalid assignments */
		if (reg >= NUM_MON_LABELS)
			continue;
		/* Skip if disabled or reserved */
		if (nct6683_mon_label[reg] == NULL)
			continue;
		if (reg < MON_VOLTAGE_START) {
			data->temp_index[data->temp_num] = i;
			data->temp_src[data->temp_num] = reg;
			data->temp_num++;
		} else {
			data->in_index[data->in_num] = i;
			data->in_src[data->in_num] = reg;
			data->in_num++;
		}
	}
}