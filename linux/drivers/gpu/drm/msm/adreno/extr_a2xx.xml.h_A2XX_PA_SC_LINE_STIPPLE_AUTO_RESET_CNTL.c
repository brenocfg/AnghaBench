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
typedef  enum a2xx_pa_sc_auto_reset_cntl { ____Placeholder_a2xx_pa_sc_auto_reset_cntl } a2xx_pa_sc_auto_reset_cntl ;

/* Variables and functions */
 int A2XX_PA_SC_LINE_STIPPLE_AUTO_RESET_CNTL__MASK ; 
 int A2XX_PA_SC_LINE_STIPPLE_AUTO_RESET_CNTL__SHIFT ; 

__attribute__((used)) static inline uint32_t A2XX_PA_SC_LINE_STIPPLE_AUTO_RESET_CNTL(enum a2xx_pa_sc_auto_reset_cntl val)
{
	return ((val) << A2XX_PA_SC_LINE_STIPPLE_AUTO_RESET_CNTL__SHIFT) & A2XX_PA_SC_LINE_STIPPLE_AUTO_RESET_CNTL__MASK;
}