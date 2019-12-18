#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vbva_record {int /*<<< orphan*/  len_and_flags; } ;
struct vbva_buf_ctx {struct vbva_record* record; TYPE_2__* vbva; scalar_t__ buffer_overflow; } ;
struct gen_pool {int dummy; } ;
struct TYPE_3__ {int host_events; } ;
struct TYPE_4__ {int record_free_index; int record_first_index; struct vbva_record* records; TYPE_1__ host_flags; } ;

/* Variables and functions */
 int VBVA_F_MODE_ENABLED ; 
 int /*<<< orphan*/  VBVA_F_RECORD_PARTIAL ; 
 int VBVA_MAX_RECORDS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  vbva_buffer_flush (struct gen_pool*) ; 

bool vbva_buffer_begin_update(struct vbva_buf_ctx *vbva_ctx,
			      struct gen_pool *ctx)
{
	struct vbva_record *record;
	u32 next;

	if (!vbva_ctx->vbva ||
	    !(vbva_ctx->vbva->host_flags.host_events & VBVA_F_MODE_ENABLED))
		return false;

	WARN_ON(vbva_ctx->buffer_overflow || vbva_ctx->record);

	next = (vbva_ctx->vbva->record_free_index + 1) % VBVA_MAX_RECORDS;

	/* Flush if all slots in the records queue are used */
	if (next == vbva_ctx->vbva->record_first_index)
		vbva_buffer_flush(ctx);

	/* If even after flush there is no place then fail the request */
	if (next == vbva_ctx->vbva->record_first_index)
		return false;

	record = &vbva_ctx->vbva->records[vbva_ctx->vbva->record_free_index];
	record->len_and_flags = VBVA_F_RECORD_PARTIAL;
	vbva_ctx->vbva->record_free_index = next;
	/* Remember which record we are using. */
	vbva_ctx->record = record;

	return true;
}