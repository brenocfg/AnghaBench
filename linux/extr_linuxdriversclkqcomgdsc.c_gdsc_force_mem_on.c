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
typedef  int u32 ;
struct gdsc {int cxc_count; int /*<<< orphan*/ * cxcs; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RETAIN_MEM ; 
 int RETAIN_PERIPH ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void gdsc_force_mem_on(struct gdsc *sc)
{
	int i;
	u32 mask = RETAIN_MEM | RETAIN_PERIPH;

	for (i = 0; i < sc->cxc_count; i++)
		regmap_update_bits(sc->regmap, sc->cxcs[i], mask, mask);
}