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
typedef  scalar_t__ u32 ;
struct venc_state {scalar_t__ venc_base; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32 venc_write(struct v4l2_subdev *sd, u32 offset, u32 val)
{
	struct venc_state *venc = to_state(sd);

	writel(val, (venc->venc_base + offset));

	return val;
}