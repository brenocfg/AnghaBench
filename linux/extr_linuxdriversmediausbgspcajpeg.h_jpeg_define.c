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
typedef  int u8 ;

/* Variables and functions */
 int JPEG_HEIGHT_OFFSET ; 
 int /*<<< orphan*/  jpeg_head ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jpeg_define(u8 *jpeg_hdr,
			int height,
			int width,
			int samplesY)
{
	memcpy(jpeg_hdr, jpeg_head, sizeof jpeg_head);
#ifndef CONEX_CAM
	jpeg_hdr[JPEG_HEIGHT_OFFSET + 0] = height >> 8;
	jpeg_hdr[JPEG_HEIGHT_OFFSET + 1] = height;
	jpeg_hdr[JPEG_HEIGHT_OFFSET + 2] = width >> 8;
	jpeg_hdr[JPEG_HEIGHT_OFFSET + 3] = width;
	jpeg_hdr[JPEG_HEIGHT_OFFSET + 6] = samplesY;
#endif
}