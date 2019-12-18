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
struct ppp_mppe_state {struct ppp_mppe_state* sha1; int /*<<< orphan*/  tfm; int /*<<< orphan*/  sha1_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct ppp_mppe_state*) ; 

__attribute__((used)) static void mppe_free(void *arg)
{
	struct ppp_mppe_state *state = (struct ppp_mppe_state *) arg;
	if (state) {
		kfree(state->sha1_digest);
		crypto_free_shash(state->sha1->tfm);
		kzfree(state->sha1);
		kzfree(state);
	}
}