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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ispif_device {scalar_t__ base; } ;
typedef  enum ispif_intf { ____Placeholder_ispif_intf } ispif_intf ;

/* Variables and functions */
 scalar_t__ ISPIF_IRQ_GLOBAL_CLEAR_CMD ; 
 scalar_t__ ISPIF_VFE_m_IRQ_CLEAR_0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ISPIF_VFE_m_IRQ_CLEAR_1 (int /*<<< orphan*/ ) ; 
 scalar_t__ ISPIF_VFE_m_IRQ_CLEAR_2 (int /*<<< orphan*/ ) ; 
 scalar_t__ ISPIF_VFE_m_IRQ_MASK_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_0_PIX0_MASK ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_0_RDI0_MASK ; 
 scalar_t__ ISPIF_VFE_m_IRQ_MASK_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_1_PIX1_MASK ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_1_RDI1_MASK ; 
 scalar_t__ ISPIF_VFE_m_IRQ_MASK_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE ; 
 int /*<<< orphan*/  ISPIF_VFE_m_IRQ_MASK_2_RDI2_MASK ; 
#define  PIX0 132 
#define  PIX1 131 
#define  RDI0 130 
#define  RDI1 129 
#define  RDI2 128 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ispif_config_irq(struct ispif_device *ispif, enum ispif_intf intf,
			     u8 vfe, u8 enable)
{
	u32 val;

	switch (intf) {
	case PIX0:
		val = readl_relaxed(ispif->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_0_PIX0_MASK;
		if (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE;
		writel_relaxed(val, ispif->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		writel_relaxed(ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE,
			       ispif->base + ISPIF_VFE_m_IRQ_CLEAR_0(vfe));
		break;
	case RDI0:
		val = readl_relaxed(ispif->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_0_RDI0_MASK;
		if (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE;
		writel_relaxed(val, ispif->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		writel_relaxed(ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE,
			       ispif->base + ISPIF_VFE_m_IRQ_CLEAR_0(vfe));
		break;
	case PIX1:
		val = readl_relaxed(ispif->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_1_PIX1_MASK;
		if (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE;
		writel_relaxed(val, ispif->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		writel_relaxed(ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE,
			       ispif->base + ISPIF_VFE_m_IRQ_CLEAR_1(vfe));
		break;
	case RDI1:
		val = readl_relaxed(ispif->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_1_RDI1_MASK;
		if (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE;
		writel_relaxed(val, ispif->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		writel_relaxed(ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE,
			       ispif->base + ISPIF_VFE_m_IRQ_CLEAR_1(vfe));
		break;
	case RDI2:
		val = readl_relaxed(ispif->base + ISPIF_VFE_m_IRQ_MASK_2(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_2_RDI2_MASK;
		if (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE;
		writel_relaxed(val, ispif->base + ISPIF_VFE_m_IRQ_MASK_2(vfe));
		writel_relaxed(ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE,
			       ispif->base + ISPIF_VFE_m_IRQ_CLEAR_2(vfe));
		break;
	}

	writel(0x1, ispif->base + ISPIF_IRQ_GLOBAL_CLEAR_CMD);
}