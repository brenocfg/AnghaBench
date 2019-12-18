#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_device {int /*<<< orphan*/  card; int /*<<< orphan*/  max_speed; } ;
struct firedtv {struct fdtv_ir_context* ir_context; int /*<<< orphan*/  isochannel; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pages; } ;
struct fdtv_ir_context {int /*<<< orphan*/  context; TYPE_1__ buffer; int /*<<< orphan*/ * pages; scalar_t__ current_packet; scalar_t__ interrupt_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_ISO_CONTEXT_MATCH_ALL_TAGS ; 
 int /*<<< orphan*/  FW_ISO_CONTEXT_RECEIVE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISO_HEADER_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int N_PACKETS ; 
 int N_PAGES ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct fw_device* device_of (struct firedtv*) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int fw_iso_buffer_init (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct firedtv*) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ ) ; 
 int fw_iso_context_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_iso ; 
 int /*<<< orphan*/  kfree (struct fdtv_ir_context*) ; 
 struct fdtv_ir_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int queue_iso (struct fdtv_ir_context*,int) ; 

int fdtv_start_iso(struct firedtv *fdtv)
{
	struct fdtv_ir_context *ctx;
	struct fw_device *device = device_of(fdtv);
	int i, err;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->context = fw_iso_context_create(device->card,
			FW_ISO_CONTEXT_RECEIVE, fdtv->isochannel,
			device->max_speed, ISO_HEADER_SIZE, handle_iso, fdtv);
	if (IS_ERR(ctx->context)) {
		err = PTR_ERR(ctx->context);
		goto fail_free;
	}

	err = fw_iso_buffer_init(&ctx->buffer, device->card,
				 N_PAGES, DMA_FROM_DEVICE);
	if (err)
		goto fail_context_destroy;

	ctx->interrupt_packet = 0;
	ctx->current_packet = 0;

	for (i = 0; i < N_PAGES; i++)
		ctx->pages[i] = page_address(ctx->buffer.pages[i]);

	for (i = 0; i < N_PACKETS; i++) {
		err = queue_iso(ctx, i);
		if (err)
			goto fail;
	}

	err = fw_iso_context_start(ctx->context, -1, 0,
				   FW_ISO_CONTEXT_MATCH_ALL_TAGS);
	if (err)
		goto fail;

	fdtv->ir_context = ctx;

	return 0;
fail:
	fw_iso_buffer_destroy(&ctx->buffer, device->card);
fail_context_destroy:
	fw_iso_context_destroy(ctx->context);
fail_free:
	kfree(ctx);

	return err;
}