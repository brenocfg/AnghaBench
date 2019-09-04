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
typedef  int u32 ;
struct atmel_pmecc_user {int* lmu; int* si; int* mu; int* dmu; int* delta; int* smu; TYPE_1__* gf_tables; } ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_2__ {int* index_of; int* alpha_to; } ;

/* Variables and functions */
 int BIT (int) ; 
 int get_sectorsize (struct atmel_pmecc_user*) ; 
 int get_strength (struct atmel_pmecc_user*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atmel_pmecc_get_sigma(struct atmel_pmecc_user *user)
{
	s16 *lmu = user->lmu;
	s16 *si = user->si;
	s32 *mu = user->mu;
	s32 *dmu = user->dmu;
	s32 *delta = user->delta;
	int degree = get_sectorsize(user) == 512 ? 13 : 14;
	int cw_len = BIT(degree) - 1;
	int strength = get_strength(user);
	int num = 2 * strength + 1;
	s16 *index_of = user->gf_tables->index_of;
	s16 *alpha_to = user->gf_tables->alpha_to;
	int i, j, k;
	u32 dmu_0_count, tmp;
	s16 *smu = user->smu;

	/* index of largest delta */
	int ro;
	int largest;
	int diff;

	dmu_0_count = 0;

	/* First Row */

	/* Mu */
	mu[0] = -1;

	memset(smu, 0, sizeof(s16) * num);
	smu[0] = 1;

	/* discrepancy set to 1 */
	dmu[0] = 1;
	/* polynom order set to 0 */
	lmu[0] = 0;
	delta[0] = (mu[0] * 2 - lmu[0]) >> 1;

	/* Second Row */

	/* Mu */
	mu[1] = 0;
	/* Sigma(x) set to 1 */
	memset(&smu[num], 0, sizeof(s16) * num);
	smu[num] = 1;

	/* discrepancy set to S1 */
	dmu[1] = si[1];

	/* polynom order set to 0 */
	lmu[1] = 0;

	delta[1] = (mu[1] * 2 - lmu[1]) >> 1;

	/* Init the Sigma(x) last row */
	memset(&smu[(strength + 1) * num], 0, sizeof(s16) * num);

	for (i = 1; i <= strength; i++) {
		mu[i + 1] = i << 1;
		/* Begin Computing Sigma (Mu+1) and L(mu) */
		/* check if discrepancy is set to 0 */
		if (dmu[i] == 0) {
			dmu_0_count++;

			tmp = ((strength - (lmu[i] >> 1) - 1) / 2);
			if ((strength - (lmu[i] >> 1) - 1) & 0x1)
				tmp += 2;
			else
				tmp += 1;

			if (dmu_0_count == tmp) {
				for (j = 0; j <= (lmu[i] >> 1) + 1; j++)
					smu[(strength + 1) * num + j] =
							smu[i * num + j];

				lmu[strength + 1] = lmu[i];
				return;
			}

			/* copy polynom */
			for (j = 0; j <= lmu[i] >> 1; j++)
				smu[(i + 1) * num + j] = smu[i * num + j];

			/* copy previous polynom order to the next */
			lmu[i + 1] = lmu[i];
		} else {
			ro = 0;
			largest = -1;
			/* find largest delta with dmu != 0 */
			for (j = 0; j < i; j++) {
				if ((dmu[j]) && (delta[j] > largest)) {
					largest = delta[j];
					ro = j;
				}
			}

			/* compute difference */
			diff = (mu[i] - mu[ro]);

			/* Compute degree of the new smu polynomial */
			if ((lmu[i] >> 1) > ((lmu[ro] >> 1) + diff))
				lmu[i + 1] = lmu[i];
			else
				lmu[i + 1] = ((lmu[ro] >> 1) + diff) * 2;

			/* Init smu[i+1] with 0 */
			for (k = 0; k < num; k++)
				smu[(i + 1) * num + k] = 0;

			/* Compute smu[i+1] */
			for (k = 0; k <= lmu[ro] >> 1; k++) {
				s16 a, b, c;

				if (!(smu[ro * num + k] && dmu[i]))
					continue;

				a = index_of[dmu[i]];
				b = index_of[dmu[ro]];
				c = index_of[smu[ro * num + k]];
				tmp = a + (cw_len - b) + c;
				a = alpha_to[tmp % cw_len];
				smu[(i + 1) * num + (k + diff)] = a;
			}

			for (k = 0; k <= lmu[i] >> 1; k++)
				smu[(i + 1) * num + k] ^= smu[i * num + k];
		}

		/* End Computing Sigma (Mu+1) and L(mu) */
		/* In either case compute delta */
		delta[i + 1] = (mu[i + 1] * 2 - lmu[i + 1]) >> 1;

		/* Do not compute discrepancy for the last iteration */
		if (i >= strength)
			continue;

		for (k = 0; k <= (lmu[i + 1] >> 1); k++) {
			tmp = 2 * (i - 1);
			if (k == 0) {
				dmu[i + 1] = si[tmp + 3];
			} else if (smu[(i + 1) * num + k] && si[tmp + 3 - k]) {
				s16 a, b, c;

				a = index_of[smu[(i + 1) * num + k]];
				b = si[2 * (i - 1) + 3 - k];
				c = index_of[b];
				tmp = a + c;
				tmp %= cw_len;
				dmu[i + 1] = alpha_to[tmp] ^ dmu[i + 1];
			}
		}
	}
}