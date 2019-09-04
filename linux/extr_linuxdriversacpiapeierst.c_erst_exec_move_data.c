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
typedef  scalar_t__ u64 ;
struct apei_exec_context {int /*<<< orphan*/  var2; scalar_t__ dst_base; scalar_t__ src_base; } ;
struct acpi_whea_header {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int __apei_exec_read_register (struct acpi_whea_header*,scalar_t__*) ; 
 scalar_t__ in_interrupt () ; 
 void* ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  memmove (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int erst_exec_move_data(struct apei_exec_context *ctx,
			       struct acpi_whea_header *entry)
{
	int rc;
	u64 offset;
	void *src, *dst;

	/* ioremap does not work in interrupt context */
	if (in_interrupt()) {
		pr_warn("MOVE_DATA can not be used in interrupt context.\n");
		return -EBUSY;
	}

	rc = __apei_exec_read_register(entry, &offset);
	if (rc)
		return rc;

	src = ioremap(ctx->src_base + offset, ctx->var2);
	if (!src)
		return -ENOMEM;
	dst = ioremap(ctx->dst_base + offset, ctx->var2);
	if (!dst) {
		iounmap(src);
		return -ENOMEM;
	}

	memmove(dst, src, ctx->var2);

	iounmap(src);
	iounmap(dst);

	return 0;
}