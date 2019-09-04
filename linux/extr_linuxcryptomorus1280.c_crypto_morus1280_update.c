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
struct morus1280_state {struct morus1280_block* s; } ;
struct morus1280_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_morus1280_round (struct morus1280_block*,struct morus1280_block*,struct morus1280_block*,struct morus1280_block*,struct morus1280_block*,struct morus1280_block const*,int,int) ; 

__attribute__((used)) static void crypto_morus1280_update(struct morus1280_state *state,
				    const struct morus1280_block *m)
{
	static const struct morus1280_block z = {};

	struct morus1280_block *s = state->s;

	crypto_morus1280_round(&s[0], &s[1], &s[2], &s[3], &s[4], &z, 13, 1);
	crypto_morus1280_round(&s[1], &s[2], &s[3], &s[4], &s[0], m,  46, 2);
	crypto_morus1280_round(&s[2], &s[3], &s[4], &s[0], &s[1], m,  38, 3);
	crypto_morus1280_round(&s[3], &s[4], &s[0], &s[1], &s[2], m,   7, 2);
	crypto_morus1280_round(&s[4], &s[0], &s[1], &s[2], &s[3], m,   4, 1);
}