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

/* Variables and functions */

__attribute__((used)) static inline int estimated_au_size(u32 w, u32 h)
{
	/*
	 * for a MJPEG stream encoded from YUV422 pixel format,
	 * assuming a compression ratio of 2, the maximum size
	 * of an access unit is (width x height x 2) / 2,
	 * so (width x height)
	 */
	return (w * h);
}