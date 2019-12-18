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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_FLG_COS ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_DHC ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_HC ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_LEADING_RSS ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_OV ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_STATS ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA_GRO ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA_IPV6 ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_VLAN ; 
 scalar_t__ IS_MF_SD (struct bnx2x*) ; 
 int VFPF_QUEUE_FLG_COS ; 
 int VFPF_QUEUE_FLG_DHC ; 
 int VFPF_QUEUE_FLG_HC ; 
 int VFPF_QUEUE_FLG_LEADING_RSS ; 
 int VFPF_QUEUE_FLG_STATS ; 
 int VFPF_QUEUE_FLG_TPA ; 
 int VFPF_QUEUE_FLG_TPA_GRO ; 
 int VFPF_QUEUE_FLG_TPA_IPV6 ; 
 int VFPF_QUEUE_FLG_VLAN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void bnx2x_vf_mbx_set_q_flags(struct bnx2x *bp, u32 mbx_q_flags,
				     unsigned long *sp_q_flags)
{
	if (mbx_q_flags & VFPF_QUEUE_FLG_TPA)
		__set_bit(BNX2X_Q_FLG_TPA, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_TPA_IPV6)
		__set_bit(BNX2X_Q_FLG_TPA_IPV6, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_TPA_GRO)
		__set_bit(BNX2X_Q_FLG_TPA_GRO, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_STATS)
		__set_bit(BNX2X_Q_FLG_STATS, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_VLAN)
		__set_bit(BNX2X_Q_FLG_VLAN, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_COS)
		__set_bit(BNX2X_Q_FLG_COS, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_HC)
		__set_bit(BNX2X_Q_FLG_HC, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_DHC)
		__set_bit(BNX2X_Q_FLG_DHC, sp_q_flags);
	if (mbx_q_flags & VFPF_QUEUE_FLG_LEADING_RSS)
		__set_bit(BNX2X_Q_FLG_LEADING_RSS, sp_q_flags);

	/* outer vlan removal is set according to PF's multi function mode */
	if (IS_MF_SD(bp))
		__set_bit(BNX2X_Q_FLG_OV, sp_q_flags);
}