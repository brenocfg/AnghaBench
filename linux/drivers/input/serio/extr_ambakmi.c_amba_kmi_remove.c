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
struct amba_kmi_port {int /*<<< orphan*/  base; int /*<<< orphan*/  clk; int /*<<< orphan*/  io; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct amba_kmi_port* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct amba_kmi_port*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amba_kmi_remove(struct amba_device *dev)
{
	struct amba_kmi_port *kmi = amba_get_drvdata(dev);

	serio_unregister_port(kmi->io);
	clk_put(kmi->clk);
	iounmap(kmi->base);
	kfree(kmi);
	amba_release_regions(dev);
	return 0;
}