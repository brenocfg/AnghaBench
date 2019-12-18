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
 int BIT_INQST_MASK_EOF ; 
 int BIT_INQST_MASK_ERROR_BS ; 
 int BIT_INQST_MASK_OVERFLOW ; 
 int BIT_INQST_MASK_PAUSE ; 
 int BIT_INQST_MASK_UNDERFLOW ; 
 int MTK_JPEG_DEC_RESULT_EOF_DONE ; 
 int MTK_JPEG_DEC_RESULT_ERROR_BS ; 
 int MTK_JPEG_DEC_RESULT_ERROR_UNKNOWN ; 
 int MTK_JPEG_DEC_RESULT_OVERFLOW ; 
 int MTK_JPEG_DEC_RESULT_PAUSE ; 
 int MTK_JPEG_DEC_RESULT_UNDERFLOW ; 

u32 mtk_jpeg_dec_enum_result(u32 irq_result)
{
	if (irq_result & BIT_INQST_MASK_EOF)
		return MTK_JPEG_DEC_RESULT_EOF_DONE;
	if (irq_result & BIT_INQST_MASK_PAUSE)
		return MTK_JPEG_DEC_RESULT_PAUSE;
	if (irq_result & BIT_INQST_MASK_UNDERFLOW)
		return MTK_JPEG_DEC_RESULT_UNDERFLOW;
	if (irq_result & BIT_INQST_MASK_OVERFLOW)
		return MTK_JPEG_DEC_RESULT_OVERFLOW;
	if (irq_result & BIT_INQST_MASK_ERROR_BS)
		return MTK_JPEG_DEC_RESULT_ERROR_BS;

	return MTK_JPEG_DEC_RESULT_ERROR_UNKNOWN;
}