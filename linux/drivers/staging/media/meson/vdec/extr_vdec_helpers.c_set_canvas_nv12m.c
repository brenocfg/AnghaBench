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
typedef  int u8 ;
typedef  int u32 ;
struct vb2_buffer {int dummy; } ;
struct amvdec_session {struct amvdec_core* core; } ;
struct amvdec_core {int /*<<< orphan*/  canvas; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_CANVAS_BLKMODE_LINEAR ; 
 int /*<<< orphan*/  MESON_CANVAS_ENDIAN_SWAP64 ; 
 int /*<<< orphan*/  MESON_CANVAS_WRAP_NONE ; 
 int NUM_CANVAS_NV12 ; 
 int /*<<< orphan*/  amvdec_write_dos (struct amvdec_core*,int,int) ; 
 int canvas_alloc (struct amvdec_session*,int*) ; 
 int /*<<< orphan*/  meson_canvas_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 

__attribute__((used)) static int set_canvas_nv12m(struct amvdec_session *sess,
			    struct vb2_buffer *vb, u32 width,
			    u32 height, u32 reg)
{
	struct amvdec_core *core = sess->core;
	u8 canvas_id[NUM_CANVAS_NV12]; /* Y U/V */
	dma_addr_t buf_paddr[NUM_CANVAS_NV12]; /* Y U/V */
	int ret, i;

	for (i = 0; i < NUM_CANVAS_NV12; ++i) {
		ret = canvas_alloc(sess, &canvas_id[i]);
		if (ret)
			return ret;

		buf_paddr[i] =
		    vb2_dma_contig_plane_dma_addr(vb, i);
	}

	/* Y plane */
	meson_canvas_config(core->canvas, canvas_id[0], buf_paddr[0],
			    width, height, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* U/V plane */
	meson_canvas_config(core->canvas, canvas_id[1], buf_paddr[1],
			    width, height / 2, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	amvdec_write_dos(core, reg,
			 ((canvas_id[1]) << 16) |
			 ((canvas_id[1]) << 8)  |
			 (canvas_id[0]));

	return 0;
}