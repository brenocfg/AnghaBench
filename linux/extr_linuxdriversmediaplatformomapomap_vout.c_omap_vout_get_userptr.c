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
typedef  int /*<<< orphan*/  u32 ;
struct videobuf_buffer {struct frame_vector* priv; } ;
struct frame_vector {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 long PAGE_OFFSET ; 
 int /*<<< orphan*/  __pfn_to_phys (int /*<<< orphan*/ ) ; 
 struct frame_vector* frame_vector_create (int) ; 
 int /*<<< orphan*/  frame_vector_destroy (struct frame_vector*) ; 
 int /*<<< orphan*/ * frame_vector_pfns (struct frame_vector*) ; 
 int get_vaddr_frames (long,int,int /*<<< orphan*/ ,struct frame_vector*) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static int omap_vout_get_userptr(struct videobuf_buffer *vb, long virtp,
				 u32 *physp)
{
	struct frame_vector *vec;
	int ret;

	/* For kernel direct-mapped memory, take the easy way */
	if (virtp >= PAGE_OFFSET) {
		*physp = virt_to_phys((void *)virtp);
		return 0;
	}

	vec = frame_vector_create(1);
	if (!vec)
		return -ENOMEM;

	ret = get_vaddr_frames(virtp, 1, FOLL_WRITE, vec);
	if (ret != 1) {
		frame_vector_destroy(vec);
		return -EINVAL;
	}
	*physp = __pfn_to_phys(frame_vector_pfns(vec)[0]);
	vb->priv = vec;

	return 0;
}