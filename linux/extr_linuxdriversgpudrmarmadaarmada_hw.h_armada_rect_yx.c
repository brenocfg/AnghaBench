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
typedef  int u32 ;
struct drm_rect {int y1; int x1; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 armada_rect_yx(struct drm_rect *r)
{
	return (r)->y1 << 16 | ((r)->x1 & 0x0000ffff);
}