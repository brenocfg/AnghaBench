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
struct atmel_pmecc_user {int* partial_syn; int* si; TYPE_1__* gf_tables; } ;
typedef  int s16 ;
struct TYPE_2__ {int* alpha_to; int* index_of; } ;

/* Variables and functions */
 int BIT (int) ; 
 int get_sectorsize (struct atmel_pmecc_user*) ; 
 int get_strength (struct atmel_pmecc_user*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atmel_pmecc_substitute(struct atmel_pmecc_user *user)
{
	int degree = get_sectorsize(user) == 512 ? 13 : 14;
	int cw_len = BIT(degree) - 1;
	int strength = get_strength(user);
	s16 *alpha_to = user->gf_tables->alpha_to;
	s16 *index_of = user->gf_tables->index_of;
	s16 *partial_syn = user->partial_syn;
	s16 *si;
	int i, j;

	/*
	 * si[] is a table that holds the current syndrome value,
	 * an element of that table belongs to the field
	 */
	si = user->si;

	memset(&si[1], 0, sizeof(s16) * ((2 * strength) - 1));

	/* Computation 2t syndromes based on S(x) */
	/* Odd syndromes */
	for (i = 1; i < 2 * strength; i += 2) {
		for (j = 0; j < degree; j++) {
			if (partial_syn[i] & BIT(j))
				si[i] = alpha_to[i * j] ^ si[i];
		}
	}
	/* Even syndrome = (Odd syndrome) ** 2 */
	for (i = 2, j = 1; j <= strength; i = ++j << 1) {
		if (si[j] == 0) {
			si[i] = 0;
		} else {
			s16 tmp;

			tmp = index_of[si[j]];
			tmp = (tmp * 2) % cw_len;
			si[i] = alpha_to[tmp];
		}
	}
}