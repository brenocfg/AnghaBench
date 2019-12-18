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
struct vbva_record {int len_and_flags; } ;
struct vbva_buf_ctx {int buffer_overflow; struct vbva_record* record; int /*<<< orphan*/  vbva; } ;

/* Variables and functions */
 int VBVA_F_RECORD_PARTIAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void vbva_buffer_end_update(struct vbva_buf_ctx *vbva_ctx)
{
	struct vbva_record *record = vbva_ctx->record;

	WARN_ON(!vbva_ctx->vbva || !record ||
		!(record->len_and_flags & VBVA_F_RECORD_PARTIAL));

	/* Mark the record completed. */
	record->len_and_flags &= ~VBVA_F_RECORD_PARTIAL;

	vbva_ctx->buffer_overflow = false;
	vbva_ctx->record = NULL;
}