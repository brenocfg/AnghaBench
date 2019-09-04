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
struct reg_pair_t {scalar_t__ reg; scalar_t__ val; } ;

/* Variables and functions */

__attribute__((used)) static void copy_reg_bits(struct reg_pair_t *reg_pair1,
			  struct reg_pair_t *reg_pair2)
{
	unsigned int i, j;

	i = j = 0;

	while (reg_pair1[i].reg || reg_pair1[i].val) {
		while (reg_pair2[j].reg || reg_pair2[j].val) {
			if (reg_pair1[i].reg != reg_pair2[j].reg) {
				j++;
				continue;
			}
			reg_pair2[j].val = reg_pair1[i].val;
			break;
		}
		i++;
	}
	return;
}