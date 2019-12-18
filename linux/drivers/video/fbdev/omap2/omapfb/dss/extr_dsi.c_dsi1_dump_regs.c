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
struct seq_file {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsi_dump_dsidev_regs (struct platform_device*,struct seq_file*) ; 
 struct platform_device* dsi_get_dsidev_from_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi1_dump_regs(struct seq_file *s)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_id(0);

	dsi_dump_dsidev_regs(dsidev, s);
}