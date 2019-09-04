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
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
#define  AMDGPU_HPD_1 133 
#define  AMDGPU_HPD_2 132 
#define  AMDGPU_HPD_3 131 
#define  AMDGPU_HPD_4 130 
#define  AMDGPU_HPD_5 129 
#define  AMDGPU_HPD_6 128 
 int DC_IRQ_SOURCE_HPD1 ; 
 int DC_IRQ_SOURCE_HPD2 ; 
 int DC_IRQ_SOURCE_HPD3 ; 
 int DC_IRQ_SOURCE_HPD4 ; 
 int DC_IRQ_SOURCE_HPD5 ; 
 int DC_IRQ_SOURCE_HPD6 ; 
 int DC_IRQ_SOURCE_INVALID ; 

__attribute__((used)) static enum dc_irq_source amdgpu_dm_hpd_to_dal_irq_source(unsigned type)
{
	switch (type) {
	case AMDGPU_HPD_1:
		return DC_IRQ_SOURCE_HPD1;
	case AMDGPU_HPD_2:
		return DC_IRQ_SOURCE_HPD2;
	case AMDGPU_HPD_3:
		return DC_IRQ_SOURCE_HPD3;
	case AMDGPU_HPD_4:
		return DC_IRQ_SOURCE_HPD4;
	case AMDGPU_HPD_5:
		return DC_IRQ_SOURCE_HPD5;
	case AMDGPU_HPD_6:
		return DC_IRQ_SOURCE_HPD6;
	default:
		return DC_IRQ_SOURCE_INVALID;
	}
}