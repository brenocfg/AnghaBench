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
typedef  int u8 ;
typedef  int u32 ;
struct ispif_device {int base; } ;
typedef  enum ispif_intf { ____Placeholder_ispif_intf } ispif_intf ;

/* Variables and functions */
 int ISPIF_VFE_m_PIX_INTF_n_CID_MASK (int,int) ; 
 int ISPIF_VFE_m_RDI_INTF_n_CID_MASK (int,int) ; 
#define  PIX0 132 
#define  PIX1 131 
#define  RDI0 130 
#define  RDI1 129 
#define  RDI2 128 
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void ispif_select_cid(struct ispif_device *ispif, enum ispif_intf intf,
			     u8 cid, u8 vfe, u8 enable)
{
	u32 cid_mask = 1 << cid;
	u32 addr = 0;
	u32 val;

	switch (intf) {
	case PIX0:
		addr = ISPIF_VFE_m_PIX_INTF_n_CID_MASK(vfe, 0);
		break;
	case RDI0:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 0);
		break;
	case PIX1:
		addr = ISPIF_VFE_m_PIX_INTF_n_CID_MASK(vfe, 1);
		break;
	case RDI1:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 1);
		break;
	case RDI2:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 2);
		break;
	}

	val = readl_relaxed(ispif->base + addr);
	if (enable)
		val |= cid_mask;
	else
		val &= ~cid_mask;

	writel(val, ispif->base + addr);
}