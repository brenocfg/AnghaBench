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
struct atmel_sha_hmac_key {int valid; unsigned int keylen; int /*<<< orphan*/  buffer; int /*<<< orphan*/  keydup; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atmel_sha_hmac_key_release (struct atmel_sha_hmac_key*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static inline int atmel_sha_hmac_key_set(struct atmel_sha_hmac_key *hkey,
					 const u8 *key,
					 unsigned int keylen)
{
	atmel_sha_hmac_key_release(hkey);

	if (keylen > sizeof(hkey->buffer)) {
		hkey->keydup = kmemdup(key, keylen, GFP_KERNEL);
		if (!hkey->keydup)
			return -ENOMEM;

	} else {
		memcpy(hkey->buffer, key, keylen);
	}

	hkey->valid = true;
	hkey->keylen = keylen;
	return 0;
}