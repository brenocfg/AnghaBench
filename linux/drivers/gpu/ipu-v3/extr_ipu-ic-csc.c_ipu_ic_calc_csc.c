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
struct ipu_ic_csc {int /*<<< orphan*/  out_cs; int /*<<< orphan*/  in_cs; } ;
typedef  enum v4l2_ycbcr_encoding { ____Placeholder_v4l2_ycbcr_encoding } v4l2_ycbcr_encoding ;
typedef  enum v4l2_quantization { ____Placeholder_v4l2_quantization } v4l2_quantization ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 int __ipu_ic_calc_csc (struct ipu_ic_csc*) ; 
 int /*<<< orphan*/  ipu_ic_fill_colorspace (int /*<<< orphan*/ *,int,int,int) ; 

int ipu_ic_calc_csc(struct ipu_ic_csc *csc,
		    enum v4l2_ycbcr_encoding in_enc,
		    enum v4l2_quantization in_quant,
		    enum ipu_color_space in_cs,
		    enum v4l2_ycbcr_encoding out_enc,
		    enum v4l2_quantization out_quant,
		    enum ipu_color_space out_cs)
{
	ipu_ic_fill_colorspace(&csc->in_cs, in_enc, in_quant, in_cs);
	ipu_ic_fill_colorspace(&csc->out_cs, out_enc, out_quant, out_cs);

	return __ipu_ic_calc_csc(csc);
}