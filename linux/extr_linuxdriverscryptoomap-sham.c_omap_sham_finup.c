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
struct omap_sham_reqctx {int /*<<< orphan*/  flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FLAGS_FINUP ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int omap_sham_final (struct ahash_request*) ; 
 int omap_sham_update (struct ahash_request*) ; 

__attribute__((used)) static int omap_sham_finup(struct ahash_request *req)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	int err1, err2;

	ctx->flags |= BIT(FLAGS_FINUP);

	err1 = omap_sham_update(req);
	if (err1 == -EINPROGRESS || err1 == -EBUSY)
		return err1;
	/*
	 * final() has to be always called to cleanup resources
	 * even if udpate() failed, except EINPROGRESS
	 */
	err2 = omap_sham_final(req);

	return err1 ?: err2;
}