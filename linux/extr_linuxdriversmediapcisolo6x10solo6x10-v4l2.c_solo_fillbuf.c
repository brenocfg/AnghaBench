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
struct vb2_v4l2_buffer {scalar_t__ sequence; } ;
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct solo_dev {unsigned int old_write; int /*<<< orphan*/  sequence; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int SOLO_DISP_EXT_ADDR ; 
 unsigned int SOLO_HW_BPL ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 scalar_t__ erase_off (struct solo_dev*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 unsigned int solo_bytesperline (struct solo_dev*) ; 
 int solo_image_size (struct solo_dev*) ; 
 int solo_p2m_dma_t (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int solo_vlines (struct solo_dev*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 void* vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void solo_fillbuf(struct solo_dev *solo_dev,
			 struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	dma_addr_t addr;
	unsigned int fdma_addr;
	int error = -1;
	int i;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	if (!addr)
		goto finish_buf;

	if (erase_off(solo_dev)) {
		void *p = vb2_plane_vaddr(vb, 0);
		int image_size = solo_image_size(solo_dev);

		for (i = 0; i < image_size; i += 2) {
			((u8 *)p)[i] = 0x80;
			((u8 *)p)[i + 1] = 0x00;
		}
		error = 0;
	} else {
		fdma_addr = SOLO_DISP_EXT_ADDR + (solo_dev->old_write *
				(SOLO_HW_BPL * solo_vlines(solo_dev)));

		error = solo_p2m_dma_t(solo_dev, 0, addr, fdma_addr,
				       solo_bytesperline(solo_dev),
				       solo_vlines(solo_dev), SOLO_HW_BPL);
	}

finish_buf:
	if (!error) {
		vb2_set_plane_payload(vb, 0,
			solo_vlines(solo_dev) * solo_bytesperline(solo_dev));
		vbuf->sequence = solo_dev->sequence++;
		vb->timestamp = ktime_get_ns();
	}

	vb2_buffer_done(vb, error ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
}