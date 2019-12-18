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
typedef  int u16 ;

/* Variables and functions */
 int GLINT_DYN_CTL_CLEARPBA_M ; 
 int GLINT_DYN_CTL_INTENA_M ; 
 int GLINT_DYN_CTL_INTERVAL_S ; 
 int GLINT_DYN_CTL_ITR_INDX_S ; 
 int ICE_ITR_GRAN_S ; 
 int ICE_ITR_MASK ; 

__attribute__((used)) static u32 ice_buildreg_itr(u16 itr_idx, u16 itr)
{
	/* The ITR value is reported in microseconds, and the register value is
	 * recorded in 2 microsecond units. For this reason we only need to
	 * shift by the GLINT_DYN_CTL_INTERVAL_S - ICE_ITR_GRAN_S to apply this
	 * granularity as a shift instead of division. The mask makes sure the
	 * ITR value is never odd so we don't accidentally write into the field
	 * prior to the ITR field.
	 */
	itr &= ICE_ITR_MASK;

	return GLINT_DYN_CTL_INTENA_M | GLINT_DYN_CTL_CLEARPBA_M |
		(itr_idx << GLINT_DYN_CTL_ITR_INDX_S) |
		(itr << (GLINT_DYN_CTL_INTERVAL_S - ICE_ITR_GRAN_S));
}