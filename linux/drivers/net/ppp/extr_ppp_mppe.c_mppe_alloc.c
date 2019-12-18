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
struct ppp_mppe_state {unsigned char* master_key; unsigned char* session_key; TYPE_1__* sha1; struct ppp_mppe_state* sha1_digest; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_2__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int CILEN_MPPE ; 
 unsigned char CI_MPPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 unsigned int MPPE_MAX_KEY_LEN ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 unsigned int crypto_shash_descsize (struct crypto_shash*) ; 
 unsigned int crypto_shash_digestsize (struct crypto_shash*) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  kfree (struct ppp_mppe_state*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 struct ppp_mppe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void *mppe_alloc(unsigned char *options, int optlen)
{
	struct ppp_mppe_state *state;
	struct crypto_shash *shash;
	unsigned int digestsize;

	if (optlen != CILEN_MPPE + sizeof(state->master_key) ||
	    options[0] != CI_MPPE || options[1] != CILEN_MPPE ||
	    fips_enabled)
		goto out;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		goto out;


	shash = crypto_alloc_shash("sha1", 0, 0);
	if (IS_ERR(shash))
		goto out_free;

	state->sha1 = kmalloc(sizeof(*state->sha1) +
				     crypto_shash_descsize(shash),
			      GFP_KERNEL);
	if (!state->sha1) {
		crypto_free_shash(shash);
		goto out_free;
	}
	state->sha1->tfm = shash;

	digestsize = crypto_shash_digestsize(shash);
	if (digestsize < MPPE_MAX_KEY_LEN)
		goto out_free;

	state->sha1_digest = kmalloc(digestsize, GFP_KERNEL);
	if (!state->sha1_digest)
		goto out_free;

	/* Save keys. */
	memcpy(state->master_key, &options[CILEN_MPPE],
	       sizeof(state->master_key));
	memcpy(state->session_key, state->master_key,
	       sizeof(state->master_key));

	/*
	 * We defer initial key generation until mppe_init(), as mppe_alloc()
	 * is called frequently during negotiation.
	 */

	return (void *)state;

out_free:
	kfree(state->sha1_digest);
	if (state->sha1) {
		crypto_free_shash(state->sha1->tfm);
		kzfree(state->sha1);
	}
	kfree(state);
out:
	return NULL;
}