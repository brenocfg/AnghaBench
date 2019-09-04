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
typedef  void* u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFX_OP_PIPE_CONTROL (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (void*,int) ; 
 int PIPE_CONTROL_CS_STALL ; 
 int PIPE_CONTROL_GLOBAL_GTT_IVB ; 
 int PIPE_CONTROL_QW_WRITE ; 

__attribute__((used)) static inline u32 *
gen8_emit_ggtt_write_rcs(u32 *cs, u32 value, u32 gtt_offset)
{
	/* We're using qword write, offset should be aligned to 8 bytes. */
	GEM_BUG_ON(!IS_ALIGNED(gtt_offset, 8));

	/* w/a for post sync ops following a GPGPU operation we
	 * need a prior CS_STALL, which is emitted by the flush
	 * following the batch.
	 */
	*cs++ = GFX_OP_PIPE_CONTROL(6);
	*cs++ = PIPE_CONTROL_GLOBAL_GTT_IVB | PIPE_CONTROL_CS_STALL |
		PIPE_CONTROL_QW_WRITE;
	*cs++ = gtt_offset;
	*cs++ = 0;
	*cs++ = value;
	/* We're thrashing one dword of HWS. */
	*cs++ = 0;

	return cs;
}