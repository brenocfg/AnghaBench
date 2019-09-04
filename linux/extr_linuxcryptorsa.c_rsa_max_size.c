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
struct rsa_mpi_key {int /*<<< orphan*/  n; } ;
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 struct rsa_mpi_key* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 unsigned int mpi_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rsa_max_size(struct crypto_akcipher *tfm)
{
	struct rsa_mpi_key *pkey = akcipher_tfm_ctx(tfm);

	return mpi_get_size(pkey->n);
}