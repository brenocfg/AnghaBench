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
struct omap_sham_reqctx {scalar_t__ bufcnt; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (struct omap_sham_reqctx*,void const*,scalar_t__) ; 

__attribute__((used)) static int omap_sham_import(struct ahash_request *req, const void *in)
{
	struct omap_sham_reqctx *rctx = ahash_request_ctx(req);
	const struct omap_sham_reqctx *ctx_in = in;

	memcpy(rctx, in, sizeof(*rctx) + ctx_in->bufcnt);

	return 0;
}