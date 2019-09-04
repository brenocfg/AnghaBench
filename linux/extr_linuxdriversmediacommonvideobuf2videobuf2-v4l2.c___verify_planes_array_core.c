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
struct vb2_buffer {int dummy; } ;

/* Variables and functions */
 int __verify_planes_array (struct vb2_buffer*,void const*) ; 

__attribute__((used)) static int __verify_planes_array_core(struct vb2_buffer *vb, const void *pb)
{
	return __verify_planes_array(vb, pb);
}