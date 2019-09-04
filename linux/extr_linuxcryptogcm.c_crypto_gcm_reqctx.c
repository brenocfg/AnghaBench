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
typedef  void crypto_gcm_req_priv_ctx ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ aead_request_ctx (struct aead_request*) ; 
 unsigned long crypto_aead_alignmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 

__attribute__((used)) static inline struct crypto_gcm_req_priv_ctx *crypto_gcm_reqctx(
	struct aead_request *req)
{
	unsigned long align = crypto_aead_alignmask(crypto_aead_reqtfm(req));

	return (void *)PTR_ALIGN((u8 *)aead_request_ctx(req), align + 1);
}