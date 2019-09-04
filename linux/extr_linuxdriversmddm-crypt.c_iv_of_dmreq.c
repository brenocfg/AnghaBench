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
struct dm_crypt_request {int dummy; } ;
struct crypt_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  any_tfm (struct crypt_config*) ; 
 int /*<<< orphan*/  any_tfm_aead (struct crypt_config*) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 scalar_t__ crypto_aead_alignmask (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_skcipher_alignmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *iv_of_dmreq(struct crypt_config *cc,
		       struct dm_crypt_request *dmreq)
{
	if (crypt_integrity_aead(cc))
		return (u8 *)ALIGN((unsigned long)(dmreq + 1),
			crypto_aead_alignmask(any_tfm_aead(cc)) + 1);
	else
		return (u8 *)ALIGN((unsigned long)(dmreq + 1),
			crypto_skcipher_alignmask(any_tfm(cc)) + 1);
}