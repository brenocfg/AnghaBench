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
struct sock {int dummy; } ;
struct aead_tfm {int /*<<< orphan*/  aead; } ;

/* Variables and functions */
 int CRYPTO_TFM_NEED_KEY ; 
 int ENOKEY ; 
 int aead_accept_parent_nokey (void*,struct sock*) ; 
 int crypto_aead_get_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aead_accept_parent(void *private, struct sock *sk)
{
	struct aead_tfm *tfm = private;

	if (crypto_aead_get_flags(tfm->aead) & CRYPTO_TFM_NEED_KEY)
		return -ENOKEY;

	return aead_accept_parent_nokey(private, sk);
}