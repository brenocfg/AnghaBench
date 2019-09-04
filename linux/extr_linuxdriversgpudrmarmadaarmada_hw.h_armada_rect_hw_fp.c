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
struct drm_rect {int dummy; } ;

/* Variables and functions */
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 

__attribute__((used)) static inline u32 armada_rect_hw_fp(struct drm_rect *r)
{
	return (drm_rect_height(r) & 0xffff0000) | drm_rect_width(r) >> 16;
}