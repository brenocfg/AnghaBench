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
typedef  enum ni_gpct_variant { ____Placeholder_ni_gpct_variant } ni_gpct_variant ;

/* Variables and functions */
 unsigned int GI_660X_PRESCALE_X2 ; 
 unsigned int GI_M_PRESCALE_X2 ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 

__attribute__((used)) static inline unsigned int GI_PRESCALE_X2(enum ni_gpct_variant variant)
{
	switch (variant) {
	case ni_gpct_variant_e_series:
	default:
		return 0;
	case ni_gpct_variant_m_series:
		return GI_M_PRESCALE_X2;
	case ni_gpct_variant_660x:
		return GI_660X_PRESCALE_X2;
	}
}