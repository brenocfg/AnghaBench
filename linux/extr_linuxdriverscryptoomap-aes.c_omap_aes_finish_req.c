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
struct omap_aes_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  engine; struct ablkcipher_request* req; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_finalize_ablkcipher_request (int /*<<< orphan*/ ,struct ablkcipher_request*,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void omap_aes_finish_req(struct omap_aes_dev *dd, int err)
{
	struct ablkcipher_request *req = dd->req;

	pr_debug("err: %d\n", err);

	crypto_finalize_ablkcipher_request(dd->engine, req, err);

	pm_runtime_mark_last_busy(dd->dev);
	pm_runtime_put_autosuspend(dd->dev);
}