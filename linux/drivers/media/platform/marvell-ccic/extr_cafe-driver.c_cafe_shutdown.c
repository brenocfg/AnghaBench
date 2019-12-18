#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct cafe_camera {TYPE_2__ mcam; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cafe_smbus_shutdown (struct cafe_camera*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cafe_camera*) ; 
 int /*<<< orphan*/  mccic_shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_shutdown(struct cafe_camera *cam)
{
	mccic_shutdown(&cam->mcam);
	cafe_smbus_shutdown(cam);
	free_irq(cam->pdev->irq, cam);
	pci_iounmap(cam->pdev, cam->mcam.regs);
}