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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct vbox_private {unsigned int num_crtcs; int /*<<< orphan*/  vbva_buffers; TYPE_1__ ddev; int /*<<< orphan*/  guest_pool; int /*<<< orphan*/ * vbva_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbva_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void vbox_accel_fini(struct vbox_private *vbox)
{
	unsigned int i;

	for (i = 0; i < vbox->num_crtcs; ++i)
		vbva_disable(&vbox->vbva_info[i], vbox->guest_pool, i);

	pci_iounmap(vbox->ddev.pdev, vbox->vbva_buffers);
}