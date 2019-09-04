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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int JPU_JPEG_HACTBL_CHR_OFFSET ; 
 int JPU_JPEG_HACTBL_LUM_OFFSET ; 
 int /*<<< orphan*/  JPU_JPEG_HACTBL_SIZE ; 
 int JPU_JPEG_HDCTBL_CHR_OFFSET ; 
 int JPU_JPEG_HDCTBL_LUM_OFFSET ; 
 int /*<<< orphan*/  JPU_JPEG_HDCTBL_SIZE ; 
 int JPU_JPEG_QTBL_CHR_OFFSET ; 
 int JPU_JPEG_QTBL_LUM_OFFSET ; 
 scalar_t__ hactbl_chr ; 
 scalar_t__ hactbl_lum ; 
 scalar_t__ hdctbl_chr ; 
 scalar_t__ hdctbl_lum ; 
 int /*<<< orphan*/  put_htbl (unsigned char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_qtbl (unsigned char*,int /*<<< orphan*/  const*) ; 
 scalar_t__* qtbl_chr ; 
 scalar_t__* qtbl_lum ; 

__attribute__((used)) static void jpu_generate_hdr(unsigned short quality, unsigned char *p)
{
	put_qtbl(p + JPU_JPEG_QTBL_LUM_OFFSET, (const u8 *)qtbl_lum[quality]);
	put_qtbl(p + JPU_JPEG_QTBL_CHR_OFFSET, (const u8 *)qtbl_chr[quality]);

	put_htbl(p + JPU_JPEG_HDCTBL_LUM_OFFSET, (const u8 *)hdctbl_lum,
		 JPU_JPEG_HDCTBL_SIZE);
	put_htbl(p + JPU_JPEG_HACTBL_LUM_OFFSET, (const u8 *)hactbl_lum,
		 JPU_JPEG_HACTBL_SIZE);

	put_htbl(p + JPU_JPEG_HDCTBL_CHR_OFFSET, (const u8 *)hdctbl_chr,
		 JPU_JPEG_HDCTBL_SIZE);
	put_htbl(p + JPU_JPEG_HACTBL_CHR_OFFSET, (const u8 *)hactbl_chr,
		 JPU_JPEG_HACTBL_SIZE);
}