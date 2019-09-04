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
struct pefile_context {int sig_offset; int /*<<< orphan*/  digest; int /*<<< orphan*/  digest_len; int /*<<< orphan*/  sig_len; } ;
struct key {int dummy; } ;
typedef  enum key_being_used_for { ____Placeholder_key_being_used_for } key_being_used_for ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pefile_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mscode_parse ; 
 int pefile_digest_pe (void const*,unsigned int,struct pefile_context*) ; 
 int pefile_parse_binary (void const*,unsigned int,struct pefile_context*) ; 
 int pefile_strip_sig_wrapper (void const*,struct pefile_context*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_pkcs7_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,struct key*,int,int /*<<< orphan*/ ,struct pefile_context*) ; 

int verify_pefile_signature(const void *pebuf, unsigned pelen,
			    struct key *trusted_keys,
			    enum key_being_used_for usage)
{
	struct pefile_context ctx;
	int ret;

	kenter("");

	memset(&ctx, 0, sizeof(ctx));
	ret = pefile_parse_binary(pebuf, pelen, &ctx);
	if (ret < 0)
		return ret;

	ret = pefile_strip_sig_wrapper(pebuf, &ctx);
	if (ret < 0)
		return ret;

	ret = verify_pkcs7_signature(NULL, 0,
				     pebuf + ctx.sig_offset, ctx.sig_len,
				     trusted_keys, usage,
				     mscode_parse, &ctx);
	if (ret < 0)
		goto error;

	pr_debug("Digest: %u [%*ph]\n",
		 ctx.digest_len, ctx.digest_len, ctx.digest);

	/* Generate the digest and check against the PKCS7 certificate
	 * contents.
	 */
	ret = pefile_digest_pe(pebuf, pelen, &ctx);

error:
	kzfree(ctx.digest);
	return ret;
}