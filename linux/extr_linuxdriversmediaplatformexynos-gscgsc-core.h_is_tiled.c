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
struct gsc_fmt {scalar_t__ pixelformat; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_NV12MT_16X16 ; 

__attribute__((used)) static inline int is_tiled(const struct gsc_fmt *fmt)
{
	return fmt->pixelformat == V4L2_PIX_FMT_NV12MT_16X16;
}