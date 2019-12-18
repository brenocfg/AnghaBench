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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_restart_one_down (struct pci_dev*) ; 
 int mlx4_restart_one_up (struct pci_dev*,int,int /*<<< orphan*/ *) ; 

int mlx4_restart_one(struct pci_dev *pdev)
{
	mlx4_restart_one_down(pdev);
	return mlx4_restart_one_up(pdev, false, NULL);
}