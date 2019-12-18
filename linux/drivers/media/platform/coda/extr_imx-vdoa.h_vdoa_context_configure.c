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
struct vdoa_ctx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int vdoa_context_configure(struct vdoa_ctx *ctx,
					 unsigned int width,
					 unsigned int height,
					 u32 pixelformat)
{
	return 0;
}