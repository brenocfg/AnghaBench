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
struct via_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCR_INTCTRL ; 
 int /*<<< orphan*/  VDE_I_C0AVEN ; 
 int /*<<< orphan*/  viacam_write_reg (struct via_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_irq_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viacam_int_disable(struct via_camera *cam)
{
	viafb_irq_disable(VDE_I_C0AVEN);
	viacam_write_reg(cam, VCR_INTCTRL, 0);
}