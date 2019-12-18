#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct ispif_device {scalar_t__ base; TYPE_1__* intf_cmd; } ;
typedef  enum ispif_intf { ____Placeholder_ispif_intf } ispif_intf ;
struct TYPE_2__ {int cmd_1; int cmd_0; } ;

/* Variables and functions */
 scalar_t__ ISPIF_VFE_m_INTF_CMD_0 (size_t) ; 
 scalar_t__ ISPIF_VFE_m_INTF_CMD_1 (size_t) ; 
 int RDI2 ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void ispif_set_intf_cmd(struct ispif_device *ispif, u8 cmd,
			       enum ispif_intf intf, u8 vfe, u8 vc)
{
	u32 *val;

	if (intf == RDI2) {
		val = &ispif->intf_cmd[vfe].cmd_1;
		*val &= ~(0x3 << (vc * 2 + 8));
		*val |= (cmd << (vc * 2 + 8));
		wmb();
		writel_relaxed(*val, ispif->base + ISPIF_VFE_m_INTF_CMD_1(vfe));
		wmb();
	} else {
		val = &ispif->intf_cmd[vfe].cmd_0;
		*val &= ~(0x3 << (vc * 2 + intf * 8));
		*val |= (cmd << (vc * 2 + intf * 8));
		wmb();
		writel_relaxed(*val, ispif->base + ISPIF_VFE_m_INTF_CMD_0(vfe));
		wmb();
	}
}