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
typedef  int /*<<< orphan*/  u8 ;
struct crypt_config {int key_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * key_string; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CRYPT_KEY_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int crypt_setkey (struct crypt_config*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crypt_wipe_key(struct crypt_config *cc)
{
	int r;

	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);
	get_random_bytes(&cc->key, cc->key_size);
	kzfree(cc->key_string);
	cc->key_string = NULL;
	r = crypt_setkey(cc);
	memset(&cc->key, 0, cc->key_size * sizeof(u8));

	return r;
}