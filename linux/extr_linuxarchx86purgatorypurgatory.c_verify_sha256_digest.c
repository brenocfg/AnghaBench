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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct sha256_state {int dummy; } ;
struct kexec_sha_region {int /*<<< orphan*/  len; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int ARRAY_SIZE (struct kexec_sha_region*) ; 
 int SHA256_DIGEST_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  purgatory_sha256_digest ; 
 struct kexec_sha_region* purgatory_sha_regions ; 
 int /*<<< orphan*/  sha256_final (struct sha256_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_init (struct sha256_state*) ; 
 int /*<<< orphan*/  sha256_update (struct sha256_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_sha256_digest(void)
{
	struct kexec_sha_region *ptr, *end;
	u8 digest[SHA256_DIGEST_SIZE];
	struct sha256_state sctx;

	sha256_init(&sctx);
	end = purgatory_sha_regions + ARRAY_SIZE(purgatory_sha_regions);

	for (ptr = purgatory_sha_regions; ptr < end; ptr++)
		sha256_update(&sctx, (uint8_t *)(ptr->start), ptr->len);

	sha256_final(&sctx, digest);

	if (memcmp(digest, purgatory_sha256_digest, sizeof(digest)))
		return 1;

	return 0;
}