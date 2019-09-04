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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct axon_msic {int /*<<< orphan*/  dcr_host; int /*<<< orphan*/  irq_domain; } ;

/* Variables and functions */
 int MSIC_CTRL_ENABLE ; 
 int MSIC_CTRL_IRQ_ENABLE ; 
 int /*<<< orphan*/  MSIC_CTRL_REG ; 
 int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axon_msic* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_get_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msic_dcr_write (struct axon_msic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axon_msi_shutdown(struct platform_device *device)
{
	struct axon_msic *msic = dev_get_drvdata(&device->dev);
	u32 tmp;

	pr_devel("axon_msi: disabling %pOF\n",
		 irq_domain_get_of_node(msic->irq_domain));
	tmp  = dcr_read(msic->dcr_host, MSIC_CTRL_REG);
	tmp &= ~MSIC_CTRL_ENABLE & ~MSIC_CTRL_IRQ_ENABLE;
	msic_dcr_write(msic, MSIC_CTRL_REG, tmp);
}