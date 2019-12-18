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
typedef  scalar_t__ u32 ;
struct vbva_record {int len_and_flags; } ;
struct vbva_buffer {scalar_t__ partial_write_tresh; scalar_t__ free_offset; scalar_t__ data_len; } ;
struct vbva_buf_ctx {int buffer_overflow; struct vbva_record* record; struct vbva_buffer* vbva; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int VBVA_F_RECORD_PARTIAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ vbva_buffer_available (struct vbva_buffer*) ; 
 int /*<<< orphan*/  vbva_buffer_flush (struct gen_pool*) ; 
 int /*<<< orphan*/  vbva_buffer_place_data_at (struct vbva_buf_ctx*,void const*,scalar_t__,scalar_t__) ; 

bool vbva_write(struct vbva_buf_ctx *vbva_ctx, struct gen_pool *ctx,
		const void *p, u32 len)
{
	struct vbva_record *record;
	struct vbva_buffer *vbva;
	u32 available;

	vbva = vbva_ctx->vbva;
	record = vbva_ctx->record;

	if (!vbva || vbva_ctx->buffer_overflow ||
	    !record || !(record->len_and_flags & VBVA_F_RECORD_PARTIAL))
		return false;

	available = vbva_buffer_available(vbva);

	while (len > 0) {
		u32 chunk = len;

		if (chunk >= available) {
			vbva_buffer_flush(ctx);
			available = vbva_buffer_available(vbva);
		}

		if (chunk >= available) {
			if (WARN_ON(available <= vbva->partial_write_tresh)) {
				vbva_ctx->buffer_overflow = true;
				return false;
			}
			chunk = available - vbva->partial_write_tresh;
		}

		vbva_buffer_place_data_at(vbva_ctx, p, chunk,
					  vbva->free_offset);

		vbva->free_offset = (vbva->free_offset + chunk) %
				    vbva->data_len;
		record->len_and_flags += chunk;
		available -= chunk;
		len -= chunk;
		p += chunk;
	}

	return true;
}