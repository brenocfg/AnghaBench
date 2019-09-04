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
struct fimc_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_NV12MT ; 

__attribute__((used)) static inline int tiled_fmt(struct fimc_fmt *fmt)
{
	return fmt->fourcc == V4L2_PIX_FMT_NV12MT;
}