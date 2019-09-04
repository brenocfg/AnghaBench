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
struct crypto_aead {int dummy; } ;
struct aead_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int) ; 
 int /*<<< orphan*/  crypto_aead_tfm (struct crypto_aead*) ; 
 int init_tfm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_tfm_aead(struct crypto_aead *tfm)
{
	crypto_aead_set_reqsize(tfm, sizeof(struct aead_ctx));
	return init_tfm(crypto_aead_tfm(tfm));
}