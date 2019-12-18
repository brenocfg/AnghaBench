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
struct ppp_mppe_state {int keylen; int /*<<< orphan*/  sha1_digest; int /*<<< orphan*/  sha1; int /*<<< orphan*/  session_key; int /*<<< orphan*/  master_key; } ;
struct TYPE_2__ {int /*<<< orphan*/  sha_pad2; int /*<<< orphan*/  sha_pad1; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_shash_final (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sha_pad ; 

__attribute__((used)) static void get_new_key_from_sha(struct ppp_mppe_state * state)
{
	crypto_shash_init(state->sha1);
	crypto_shash_update(state->sha1, state->master_key,
			    state->keylen);
	crypto_shash_update(state->sha1, sha_pad->sha_pad1,
			    sizeof(sha_pad->sha_pad1));
	crypto_shash_update(state->sha1, state->session_key,
			    state->keylen);
	crypto_shash_update(state->sha1, sha_pad->sha_pad2,
			    sizeof(sha_pad->sha_pad2));
	crypto_shash_final(state->sha1, state->sha1_digest);
}