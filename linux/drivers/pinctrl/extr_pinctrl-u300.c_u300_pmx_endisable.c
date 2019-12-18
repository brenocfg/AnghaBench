#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct u300_pmx_mask {int /*<<< orphan*/  mask; int /*<<< orphan*/  bits; } ;
struct u300_pmx {scalar_t__ virtbase; } ;
struct TYPE_2__ {struct u300_pmx_mask* mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 TYPE_1__* u300_pmx_functions ; 
 scalar_t__* u300_pmx_registers ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void u300_pmx_endisable(struct u300_pmx *upmx, unsigned selector,
			       bool enable)
{
	u16 regval, val, mask;
	int i;
	const struct u300_pmx_mask *upmx_mask;

	upmx_mask = u300_pmx_functions[selector].mask;
	for (i = 0; i < ARRAY_SIZE(u300_pmx_registers); i++) {
		if (enable)
			val = upmx_mask->bits;
		else
			val = 0;

		mask = upmx_mask->mask;
		if (mask != 0) {
			regval = readw(upmx->virtbase + u300_pmx_registers[i]);
			regval &= ~mask;
			regval |= val;
			writew(regval, upmx->virtbase + u300_pmx_registers[i]);
		}
		upmx_mask++;
	}
}