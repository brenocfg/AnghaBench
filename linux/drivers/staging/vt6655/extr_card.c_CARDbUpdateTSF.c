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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vnt_private {scalar_t__ PortOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbGetCurrentTSF (struct vnt_private*,scalar_t__*) ; 
 scalar_t__ CARDqGetTSFOffset (unsigned char,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MAC_REG_TFTCTL ; 
 scalar_t__ MAC_REG_TSFOFST ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFTCTL_TSFSYNCEN ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 

bool CARDbUpdateTSF(struct vnt_private *priv, unsigned char byRxRate,
		    u64 qwBSSTimestamp)
{
	u64 local_tsf;
	u64 qwTSFOffset = 0;

	CARDbGetCurrentTSF(priv, &local_tsf);

	if (qwBSSTimestamp != local_tsf) {
		qwTSFOffset = CARDqGetTSFOffset(byRxRate, qwBSSTimestamp,
						local_tsf);
		/* adjust TSF, HW's TSF add TSF Offset reg */
		VNSvOutPortD(priv->PortOffset + MAC_REG_TSFOFST,
			     (u32)qwTSFOffset);
		VNSvOutPortD(priv->PortOffset + MAC_REG_TSFOFST + 4,
			     (u32)(qwTSFOffset >> 32));
		MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL,
			      TFTCTL_TSFSYNCEN);
	}
	return true;
}