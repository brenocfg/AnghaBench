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
struct vb2_buffer {unsigned int num_planes; TYPE_1__* planes; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_priv; } ;

/* Variables and functions */
 void* call_ptr_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cookie ; 

void *vb2_plane_cookie(struct vb2_buffer *vb, unsigned int plane_no)
{
	if (plane_no >= vb->num_planes || !vb->planes[plane_no].mem_priv)
		return NULL;

	return call_ptr_memop(vb, cookie, vb->planes[plane_no].mem_priv);
}