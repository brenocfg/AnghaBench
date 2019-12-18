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
 int I40E_ITR_MASK ; 
 int const I40E_PFINT_DYN_CTLN_INTENA_MASK ; 
 int I40E_PFINT_DYN_CTLN_INTERVAL_SHIFT ; 
 int const I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT ; 

__attribute__((used)) static inline u32 i40e_buildreg_itr(const int type, u16 itr)
{
	u32 val;

	/* We don't bother with setting the CLEARPBA bit as the data sheet
	 * points out doing so is "meaningless since it was already
	 * auto-cleared". The auto-clearing happens when the interrupt is
	 * asserted.
	 *
	 * Hardware errata 28 for also indicates that writing to a
	 * xxINT_DYN_CTLx CSR with INTENA_MSK (bit 31) set to 0 will clear
	 * an event in the PBA anyway so we need to rely on the automask
	 * to hold pending events for us until the interrupt is re-enabled
	 *
	 * The itr value is reported in microseconds, and the register
	 * value is recorded in 2 microsecond units. For this reason we
	 * only need to shift by the interval shift - 1 instead of the
	 * full value.
	 */
	itr &= I40E_ITR_MASK;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
	      (type << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT) |
	      (itr << (I40E_PFINT_DYN_CTLN_INTERVAL_SHIFT - 1));

	return val;
}