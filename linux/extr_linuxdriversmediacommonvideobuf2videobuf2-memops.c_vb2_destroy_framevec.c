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
struct frame_vector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  frame_vector_destroy (struct frame_vector*) ; 
 int /*<<< orphan*/  put_vaddr_frames (struct frame_vector*) ; 

void vb2_destroy_framevec(struct frame_vector *vec)
{
	put_vaddr_frames(vec);
	frame_vector_destroy(vec);
}