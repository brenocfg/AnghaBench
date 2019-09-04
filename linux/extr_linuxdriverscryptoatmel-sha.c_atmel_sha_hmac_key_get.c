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
struct atmel_sha_hmac_key {unsigned int keylen; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * keydup; int /*<<< orphan*/  valid; } ;

/* Variables and functions */

__attribute__((used)) static inline bool atmel_sha_hmac_key_get(const struct atmel_sha_hmac_key *hkey,
					  const u8 **key,
					  unsigned int *keylen)
{
	if (!hkey->valid)
		return false;

	*keylen = hkey->keylen;
	*key = (hkey->keydup) ? hkey->keydup : hkey->buffer;
	return true;
}