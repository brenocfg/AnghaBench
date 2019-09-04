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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sha512_base_do_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int sha512_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha512_generic_block_fn ; 

int crypto_sha512_finup(struct shash_desc *desc, const u8 *data,
			unsigned int len, u8 *hash)
{
	sha512_base_do_update(desc, data, len, sha512_generic_block_fn);
	return sha512_final(desc, hash);
}