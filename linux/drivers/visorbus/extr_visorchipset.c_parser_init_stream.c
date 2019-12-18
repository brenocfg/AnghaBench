#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct visor_controlvm_parameters_header {int dummy; } ;
struct parser_context {unsigned long allocbytes; scalar_t__ param_bytes; int byte_stream; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ controlvm_payload_bytes_buffered; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_CONTROLVM_PAYLOAD_BYTES ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 TYPE_1__* chipset_dev ; 
 int /*<<< orphan*/  kfree (struct parser_context*) ; 
 struct parser_context* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 void* memremap (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (void*) ; 

__attribute__((used)) static struct parser_context *parser_init_stream(u64 addr, u32 bytes,
						 bool *retry)
{
	unsigned long allocbytes;
	struct parser_context *ctx;
	void *mapping;

	*retry = false;
	/* alloc an extra byte to ensure payload is \0 terminated */
	allocbytes = (unsigned long)bytes + 1 + (sizeof(struct parser_context) -
		     sizeof(struct visor_controlvm_parameters_header));
	if ((chipset_dev->controlvm_payload_bytes_buffered + bytes) >
	     MAX_CONTROLVM_PAYLOAD_BYTES) {
		*retry = true;
		return NULL;
	}
	ctx = kzalloc(allocbytes, GFP_KERNEL);
	if (!ctx) {
		*retry = true;
		return NULL;
	}
	ctx->allocbytes = allocbytes;
	ctx->param_bytes = bytes;
	mapping = memremap(addr, bytes, MEMREMAP_WB);
	if (!mapping)
		goto err_finish_ctx;
	memcpy(&ctx->data, mapping, bytes);
	memunmap(mapping);
	ctx->byte_stream = true;
	chipset_dev->controlvm_payload_bytes_buffered += ctx->param_bytes;
	return ctx;

err_finish_ctx:
	kfree(ctx);
	return NULL;
}