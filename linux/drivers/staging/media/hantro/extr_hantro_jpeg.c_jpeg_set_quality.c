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
 int CHROMA_QUANT_OFF ; 
 int LUMA_QUANT_OFF ; 
 int /*<<< orphan*/  chroma_q_table ; 
 int /*<<< orphan*/  jpeg_scale_quant_table (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luma_q_table ; 

__attribute__((used)) static void jpeg_set_quality(unsigned char *buffer, int quality)
{
	int scale;

	/*
	 * Non-linear scaling factor:
	 * [5,50] -> [1000..100], [51,100] -> [98..0]
	 */
	if (quality < 50)
		scale = 5000 / quality;
	else
		scale = 200 - 2 * quality;

	jpeg_scale_quant_table(buffer + LUMA_QUANT_OFF,
			       luma_q_table, scale);
	jpeg_scale_quant_table(buffer + CHROMA_QUANT_OFF,
			       chroma_q_table, scale);
}