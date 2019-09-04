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
struct atmel_sha_dev {int dummy; } ;

/* Variables and functions */
 int atmel_sha_cpu_hash (struct atmel_sha_dev*,int /*<<< orphan*/  const*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_hmac_prehash_key_done ; 

__attribute__((used)) static int atmel_sha_hmac_prehash_key(struct atmel_sha_dev *dd,
				      const u8 *key, unsigned int keylen)
{
	return atmel_sha_cpu_hash(dd, key, keylen, true,
				  atmel_sha_hmac_prehash_key_done);
}