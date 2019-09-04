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
struct v4l2_plane_pix_format {unsigned int sizeimage; unsigned int bytesperline; } ;

/* Variables and functions */
 unsigned int CEU_MAX_BPL ; 
 int /*<<< orphan*/  memset (struct v4l2_plane_pix_format*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ceu_update_plane_sizes(struct v4l2_plane_pix_format *plane,
				   unsigned int bpl, unsigned int szimage)
{
	memset(plane, 0, sizeof(*plane));

	plane->sizeimage = szimage;
	if (plane->bytesperline < bpl || plane->bytesperline > CEU_MAX_BPL)
		plane->bytesperline = bpl;
}