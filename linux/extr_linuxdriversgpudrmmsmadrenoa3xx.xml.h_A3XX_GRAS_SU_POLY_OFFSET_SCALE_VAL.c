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
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int A3XX_GRAS_SU_POLY_OFFSET_SCALE_VAL__MASK ; 
 int A3XX_GRAS_SU_POLY_OFFSET_SCALE_VAL__SHIFT ; 

__attribute__((used)) static inline uint32_t A3XX_GRAS_SU_POLY_OFFSET_SCALE_VAL(float val)
{
	return ((((int32_t)(val * 1048576.0))) << A3XX_GRAS_SU_POLY_OFFSET_SCALE_VAL__SHIFT) & A3XX_GRAS_SU_POLY_OFFSET_SCALE_VAL__MASK;
}