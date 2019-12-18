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

/* Variables and functions */
 int A2XX_VGT_CURRENT_BIN_ID_MAX_GUARD_BAND_MASK__MASK ; 
 int A2XX_VGT_CURRENT_BIN_ID_MAX_GUARD_BAND_MASK__SHIFT ; 

__attribute__((used)) static inline uint32_t A2XX_VGT_CURRENT_BIN_ID_MAX_GUARD_BAND_MASK(uint32_t val)
{
	return ((val) << A2XX_VGT_CURRENT_BIN_ID_MAX_GUARD_BAND_MASK__SHIFT) & A2XX_VGT_CURRENT_BIN_ID_MAX_GUARD_BAND_MASK__MASK;
}