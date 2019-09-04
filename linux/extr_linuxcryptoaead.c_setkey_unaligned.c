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
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int (* setkey ) (struct crypto_aead*,int /*<<< orphan*/ *,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,unsigned long) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* crypto_aead_alg (struct crypto_aead*) ; 
 unsigned long crypto_aead_alignmask (struct crypto_aead*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct crypto_aead*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int setkey_unaligned(struct crypto_aead *tfm, const u8 *key,
			    unsigned int keylen)
{
	unsigned long alignmask = crypto_aead_alignmask(tfm);
	int ret;
	u8 *buffer, *alignbuffer;
	unsigned long absize;

	absize = keylen + alignmask;
	buffer = kmalloc(absize, GFP_ATOMIC);
	if (!buffer)
		return -ENOMEM;

	alignbuffer = (u8 *)ALIGN((unsigned long)buffer, alignmask + 1);
	memcpy(alignbuffer, key, keylen);
	ret = crypto_aead_alg(tfm)->setkey(tfm, alignbuffer, keylen);
	memset(alignbuffer, 0, keylen);
	kfree(buffer);
	return ret;
}