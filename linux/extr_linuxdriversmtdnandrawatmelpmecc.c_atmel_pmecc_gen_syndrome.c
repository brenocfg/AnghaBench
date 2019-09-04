#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct atmel_pmecc_user {int* partial_syn; TYPE_2__* pmecc; } ;
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 scalar_t__ ATMEL_PMECC_REM (int,int) ; 
 int get_strength (struct atmel_pmecc_user*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void atmel_pmecc_gen_syndrome(struct atmel_pmecc_user *user, int sector)
{
	int strength = get_strength(user);
	u32 value;
	int i;

	/* Fill odd syndromes */
	for (i = 0; i < strength; i++) {
		value = readl_relaxed(user->pmecc->regs.base +
				      ATMEL_PMECC_REM(sector, i / 2));
		if (i & 1)
			value >>= 16;

		user->partial_syn[(2 * i) + 1] = value;
	}
}