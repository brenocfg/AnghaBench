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
struct cedrus_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_vb2_v4l2_buffer (struct vb2_buffer const*) ; 
 struct cedrus_buffer* vb2_v4l2_to_cedrus_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cedrus_buffer *
vb2_to_cedrus_buffer(const struct vb2_buffer *p)
{
	return vb2_v4l2_to_cedrus_buffer(to_vb2_v4l2_buffer(p));
}