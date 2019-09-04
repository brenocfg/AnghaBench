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
typedef  int /*<<< orphan*/  u32 ;
struct shash_desc {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ppc_spe_sha256_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ppc_spe_sha224_final(struct shash_desc *desc, u8 *out)
{
	u32 D[SHA256_DIGEST_SIZE >> 2];
	__be32 *dst = (__be32 *)out;

	ppc_spe_sha256_final(desc, (u8 *)D);

	/* avoid bytewise memcpy */
	dst[0] = D[0];
	dst[1] = D[1];
	dst[2] = D[2];
	dst[3] = D[3];
	dst[4] = D[4];
	dst[5] = D[5];
	dst[6] = D[6];

	/* clear sensitive data */
	memzero_explicit(D, SHA256_DIGEST_SIZE);
	return 0;
}