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
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* persist; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 

__attribute__((used)) static void get_name(struct mlx4_ib_dev *dev, char *name, int i, int max)
{
	/* pci_name format is: bus:dev:func -> xxxx:yy:zz.n
	 * with no ARI only 3 last bits are used so when the fn is higher than 8
	 * need to add it to the dev num, so count in the last number will be
	 * modulo 8 */
	snprintf(name, max, "%.8s%.2d.%d", pci_name(dev->dev->persist->pdev),
		 i / 8, i % 8);
}