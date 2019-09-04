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
struct crypt_config {int /*<<< orphan*/  flags; scalar_t__ key_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * key_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CRYPT_KEY_VALID ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int crypt_set_keyring_key (struct crypt_config*,char*) ; 
 int crypt_setkey (struct crypt_config*) ; 
 scalar_t__ hex2bin (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int crypt_set_key(struct crypt_config *cc, char *key)
{
	int r = -EINVAL;
	int key_string_len = strlen(key);

	/* Hyphen (which gives a key_size of zero) means there is no key. */
	if (!cc->key_size && strcmp(key, "-"))
		goto out;

	/* ':' means the key is in kernel keyring, short-circuit normal key processing */
	if (key[0] == ':') {
		r = crypt_set_keyring_key(cc, key + 1);
		goto out;
	}

	/* clear the flag since following operations may invalidate previously valid key */
	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);

	/* wipe references to any kernel keyring key */
	kzfree(cc->key_string);
	cc->key_string = NULL;

	/* Decode key from its hex representation. */
	if (cc->key_size && hex2bin(cc->key, key, cc->key_size) < 0)
		goto out;

	r = crypt_setkey(cc);
	if (!r)
		set_bit(DM_CRYPT_KEY_VALID, &cc->flags);

out:
	/* Hex key string not needed after here, so wipe it. */
	memset(key, '0', key_string_len);

	return r;
}