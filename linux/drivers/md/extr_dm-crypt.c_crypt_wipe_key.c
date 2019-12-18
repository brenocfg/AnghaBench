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
typedef  int /*<<< orphan*/  u8 ;
struct crypt_config {int key_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * key_string; TYPE_1__* iv_gen_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int (* wipe ) (struct crypt_config*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CRYPT_KEY_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int crypt_setkey (struct crypt_config*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct crypt_config*) ; 

__attribute__((used)) static int crypt_wipe_key(struct crypt_config *cc)
{
	int r;

	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);
	get_random_bytes(&cc->key, cc->key_size);

	/* Wipe IV private keys */
	if (cc->iv_gen_ops && cc->iv_gen_ops->wipe) {
		r = cc->iv_gen_ops->wipe(cc);
		if (r)
			return r;
	}

	kzfree(cc->key_string);
	cc->key_string = NULL;
	r = crypt_setkey(cc);
	memset(&cc->key, 0, cc->key_size * sizeof(u8));

	return r;
}