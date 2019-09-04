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
struct r5l_recovery_ctx {int total_pages; int /*<<< orphan*/  ra_bio; int /*<<< orphan*/ * ra_pool; } ;
struct r5l_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r5l_recovery_free_ra_pool(struct r5l_log *log,
					struct r5l_recovery_ctx *ctx)
{
	int i;

	for (i = 0; i < ctx->total_pages; ++i)
		put_page(ctx->ra_pool[i]);
	bio_put(ctx->ra_bio);
}