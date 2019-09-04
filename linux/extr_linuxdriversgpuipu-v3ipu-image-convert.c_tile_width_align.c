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
struct ipu_image_pixfmt {int uv_width_dec; scalar_t__ planar; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 tile_width_align(const struct ipu_image_pixfmt *fmt)
{
	return fmt->planar ? 8 * fmt->uv_width_dec : 8;
}