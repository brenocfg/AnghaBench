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
struct ispif_device {scalar_t__ base; } ;
typedef  enum ispif_intf { ____Placeholder_ispif_intf } ispif_intf ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ ISPIF_VFE_m_INTF_INPUT_SEL (int) ; 
#define  PIX0 132 
#define  PIX1 131 
#define  RDI0 130 
#define  RDI1 129 
#define  RDI2 128 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ispif_select_csid(struct ispif_device *ispif, enum ispif_intf intf,
			      u8 csid, u8 vfe, u8 enable)
{
	u32 val;

	val = readl_relaxed(ispif->base + ISPIF_VFE_m_INTF_INPUT_SEL(vfe));
	switch (intf) {
	case PIX0:
		val &= ~(BIT(1) | BIT(0));
		if (enable)
			val |= csid;
		break;
	case RDI0:
		val &= ~(BIT(5) | BIT(4));
		if (enable)
			val |= (csid << 4);
		break;
	case PIX1:
		val &= ~(BIT(9) | BIT(8));
		if (enable)
			val |= (csid << 8);
		break;
	case RDI1:
		val &= ~(BIT(13) | BIT(12));
		if (enable)
			val |= (csid << 12);
		break;
	case RDI2:
		val &= ~(BIT(21) | BIT(20));
		if (enable)
			val |= (csid << 20);
		break;
	}

	writel(val, ispif->base + ISPIF_VFE_m_INTF_INPUT_SEL(vfe));
}