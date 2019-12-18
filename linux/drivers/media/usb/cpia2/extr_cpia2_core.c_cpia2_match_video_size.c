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

/* Variables and functions */
 int STV_IMAGE_CIF_COLS ; 
 int STV_IMAGE_CIF_ROWS ; 
 int STV_IMAGE_QCIF_COLS ; 
 int STV_IMAGE_QCIF_ROWS ; 
 int STV_IMAGE_QVGA_COLS ; 
 int STV_IMAGE_QVGA_ROWS ; 
 int STV_IMAGE_VGA_COLS ; 
 int STV_IMAGE_VGA_ROWS ; 
 int VIDEOSIZE_192_144 ; 
 int VIDEOSIZE_224_168 ; 
 int VIDEOSIZE_256_192 ; 
 int VIDEOSIZE_288_216 ; 
 int VIDEOSIZE_CIF ; 
 int VIDEOSIZE_QCIF ; 
 int VIDEOSIZE_QVGA ; 
 int VIDEOSIZE_VGA ; 

int cpia2_match_video_size(int width, int height)
{
	if (width >= STV_IMAGE_VGA_COLS && height >= STV_IMAGE_VGA_ROWS)
		return VIDEOSIZE_VGA;

	if (width >= STV_IMAGE_CIF_COLS && height >= STV_IMAGE_CIF_ROWS)
		return VIDEOSIZE_CIF;

	if (width >= STV_IMAGE_QVGA_COLS && height >= STV_IMAGE_QVGA_ROWS)
		return VIDEOSIZE_QVGA;

	if (width >= 288 && height >= 216)
		return VIDEOSIZE_288_216;

	if (width >= 256 && height >= 192)
		return VIDEOSIZE_256_192;

	if (width >= 224 && height >= 168)
		return VIDEOSIZE_224_168;

	if (width >= 192 && height >= 144)
		return VIDEOSIZE_192_144;

	if (width >= STV_IMAGE_QCIF_COLS && height >= STV_IMAGE_QCIF_ROWS)
		return VIDEOSIZE_QCIF;

	return -1;
}