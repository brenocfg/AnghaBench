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
struct tps62360_chip {int* lru_index; int* curr_vset_vsel; } ;

/* Variables and functions */

__attribute__((used)) static bool find_voltage_set_register(struct tps62360_chip *tps,
		int req_vsel, int *vset_reg_id)
{
	int i;
	bool found = false;
	int new_vset_reg = tps->lru_index[3];
	int found_index = 3;

	for (i = 0; i < 4; ++i) {
		if (tps->curr_vset_vsel[tps->lru_index[i]] == req_vsel) {
			new_vset_reg = tps->lru_index[i];
			found_index = i;
			found = true;
			goto update_lru_index;
		}
	}

update_lru_index:
	for (i = found_index; i > 0; i--)
		tps->lru_index[i] = tps->lru_index[i - 1];

	tps->lru_index[0] = new_vset_reg;
	*vset_reg_id = new_vset_reg;
	return found;
}