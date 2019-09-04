#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct crypto_shash {int dummy; } ;
struct TYPE_4__ {int flags; struct crypto_shash* tfm; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int s5p_hash_shash_digest(struct crypto_shash *tfm, u32 flags,
				 const u8 *data, unsigned int len, u8 *out)
{
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;
	shash->flags = flags & ~CRYPTO_TFM_REQ_MAY_SLEEP;

	return crypto_shash_digest(shash, data, len, out);
}