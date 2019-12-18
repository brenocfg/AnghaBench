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
typedef  scalar_t__ u16 ;
struct vb2_buffer {int dummy; } ;
struct coda_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ EOI_MARKER ; 
 scalar_t__ SOI_MARKER ; 
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 int vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 void* vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int) ; 

bool coda_jpeg_check_buffer(struct coda_ctx *ctx, struct vb2_buffer *vb)
{
	void *vaddr = vb2_plane_vaddr(vb, 0);
	u16 soi, eoi;
	int len, i;

	soi = be16_to_cpup((__be16 *)vaddr);
	if (soi != SOI_MARKER)
		return false;

	len = vb2_get_plane_payload(vb, 0);
	vaddr += len - 2;
	for (i = 0; i < 32; i++) {
		eoi = be16_to_cpup((__be16 *)(vaddr - i));
		if (eoi == EOI_MARKER) {
			if (i > 0)
				vb2_set_plane_payload(vb, 0, len - i);
			return true;
		}
	}

	return false;
}