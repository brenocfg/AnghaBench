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
struct coda_ctx {int /*<<< orphan*/  debugfs_entry; int /*<<< orphan*/  dev; } ;
struct coda_aux_buf {int dummy; } ;

/* Variables and functions */
 int coda_alloc_aux_buf (int /*<<< orphan*/ ,struct coda_aux_buf*,size_t,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int coda_alloc_context_buf(struct coda_ctx *ctx,
					 struct coda_aux_buf *buf, size_t size,
					 const char *name)
{
	return coda_alloc_aux_buf(ctx->dev, buf, size, name, ctx->debugfs_entry);
}