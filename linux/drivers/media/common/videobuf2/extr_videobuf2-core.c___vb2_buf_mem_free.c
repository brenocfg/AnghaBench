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
struct vb2_buffer {unsigned int num_planes; int /*<<< orphan*/  index; TYPE_1__* planes; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mem_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put ; 

__attribute__((used)) static void __vb2_buf_mem_free(struct vb2_buffer *vb)
{
	unsigned int plane;

	for (plane = 0; plane < vb->num_planes; ++plane) {
		call_void_memop(vb, put, vb->planes[plane].mem_priv);
		vb->planes[plane].mem_priv = NULL;
		dprintk(3, "freed plane %d of buffer %d\n", plane, vb->index);
	}
}