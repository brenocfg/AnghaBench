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
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void get_name(struct mlx4_ib_dev *dev, char *name, int i, int max)
{
	char base_name[9];

	/* pci_name format is: bus:dev:func -> xxxx:yy:zz.n */
	strlcpy(name, pci_name(dev->dev->persist->pdev), max);
	strncpy(base_name, name, 8); /*till xxxx:yy:*/
	base_name[8] = '\0';
	/* with no ARI only 3 last bits are used so when the fn is higher than 8
	 * need to add it to the dev num, so count in the last number will be
	 * modulo 8 */
	sprintf(name, "%s%.2d.%d", base_name, (i/8), (i%8));
}