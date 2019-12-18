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
union vnt_phy_field_swap {int /*<<< orphan*/  field_write; int /*<<< orphan*/ * swap; int /*<<< orphan*/  field_read; } ;
typedef  int /*<<< orphan*/  u8 ;
struct vnt_private {int /*<<< orphan*/  lock; scalar_t__ PortOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDwGetCCKControlRate (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDwGetOFDMControlRate (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_REG_RSPINF_A_12 ; 
 scalar_t__ MAC_REG_RSPINF_A_18 ; 
 scalar_t__ MAC_REG_RSPINF_A_24 ; 
 scalar_t__ MAC_REG_RSPINF_A_36 ; 
 scalar_t__ MAC_REG_RSPINF_A_48 ; 
 scalar_t__ MAC_REG_RSPINF_A_54 ; 
 scalar_t__ MAC_REG_RSPINF_A_6 ; 
 scalar_t__ MAC_REG_RSPINF_A_72 ; 
 scalar_t__ MAC_REG_RSPINF_A_9 ; 
 scalar_t__ MAC_REG_RSPINF_B_1 ; 
 scalar_t__ MAC_REG_RSPINF_B_11 ; 
 scalar_t__ MAC_REG_RSPINF_B_2 ; 
 scalar_t__ MAC_REG_RSPINF_B_5 ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int /*<<< orphan*/  MAKEWORD (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  RATE_11M ; 
 int /*<<< orphan*/  RATE_12M ; 
 int /*<<< orphan*/  RATE_18M ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_24M ; 
 int /*<<< orphan*/  RATE_2M ; 
 int /*<<< orphan*/  RATE_36M ; 
 int /*<<< orphan*/  RATE_48M ; 
 int /*<<< orphan*/  RATE_54M ; 
 int /*<<< orphan*/  RATE_5M ; 
 int /*<<< orphan*/  RATE_6M ; 
 int /*<<< orphan*/  RATE_9M ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_vCalculateOFDMRParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void CARDvSetRSPINF(struct vnt_private *priv, u8 bb_type)
{
	union vnt_phy_field_swap phy;
	unsigned char byTxRate, byRsvTime;      /* For OFDM */
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Set to Page1 */
	MACvSelectPage1(priv->PortOffset);

	/* RSPINF_b_1 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_1M),
			  PK_TYPE_11B, &phy.field_read);

	 /* swap over to get correct write order */
	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_1, phy.field_write);

	/* RSPINF_b_2 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_2M),
			  PK_TYPE_11B, &phy.field_read);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_2, phy.field_write);

	/* RSPINF_b_5 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_5M),
			  PK_TYPE_11B, &phy.field_read);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_5, phy.field_write);

	/* RSPINF_b_11 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_11M),
			  PK_TYPE_11B, &phy.field_read);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_11, phy.field_write);

	/* RSPINF_a_6 */
	s_vCalculateOFDMRParameter(RATE_6M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_6,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_9 */
	s_vCalculateOFDMRParameter(RATE_9M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_9,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_12 */
	s_vCalculateOFDMRParameter(RATE_12M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_12,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_18 */
	s_vCalculateOFDMRParameter(RATE_18M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_18,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_24 */
	s_vCalculateOFDMRParameter(RATE_24M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_24,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_36 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate(
							   (void *)priv,
							   RATE_36M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_36,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_48 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate(
							   (void *)priv,
							   RATE_48M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_48,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_54 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate(
							   (void *)priv,
							   RATE_54M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_54,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_72 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate(
							   (void *)priv,
							   RATE_54M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_72,
		     MAKEWORD(byTxRate, byRsvTime));
	/* Set to Page0 */
	MACvSelectPage0(priv->PortOffset);

	spin_unlock_irqrestore(&priv->lock, flags);
}