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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_hw_ctl {int dummy; } ;
typedef  enum dpu_sspp { ____Placeholder_dpu_sspp } dpu_sspp ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
#define  SSPP_CURSOR0 141 
#define  SSPP_CURSOR1 140 
#define  SSPP_DMA0 139 
#define  SSPP_DMA1 138 
#define  SSPP_DMA2 137 
#define  SSPP_DMA3 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 

__attribute__((used)) static uint32_t dpu_hw_ctl_get_bitmask_sspp(struct dpu_hw_ctl *ctx,
	enum dpu_sspp sspp)
{
	uint32_t flushbits = 0;

	switch (sspp) {
	case SSPP_VIG0:
		flushbits =  BIT(0);
		break;
	case SSPP_VIG1:
		flushbits = BIT(1);
		break;
	case SSPP_VIG2:
		flushbits = BIT(2);
		break;
	case SSPP_VIG3:
		flushbits = BIT(18);
		break;
	case SSPP_RGB0:
		flushbits = BIT(3);
		break;
	case SSPP_RGB1:
		flushbits = BIT(4);
		break;
	case SSPP_RGB2:
		flushbits = BIT(5);
		break;
	case SSPP_RGB3:
		flushbits = BIT(19);
		break;
	case SSPP_DMA0:
		flushbits = BIT(11);
		break;
	case SSPP_DMA1:
		flushbits = BIT(12);
		break;
	case SSPP_DMA2:
		flushbits = BIT(24);
		break;
	case SSPP_DMA3:
		flushbits = BIT(25);
		break;
	case SSPP_CURSOR0:
		flushbits = BIT(22);
		break;
	case SSPP_CURSOR1:
		flushbits = BIT(23);
		break;
	default:
		break;
	}

	return flushbits;
}