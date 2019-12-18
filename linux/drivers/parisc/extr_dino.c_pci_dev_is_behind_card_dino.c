#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct dino_device {TYPE_3__ hba; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 struct dino_device* DINO_DEV (int /*<<< orphan*/ ) ; 
 int is_card_dino (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parisc_walk_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_dev_is_behind_card_dino(struct pci_dev *dev)
{
	struct dino_device *dino_dev;

	dino_dev = DINO_DEV(parisc_walk_tree(dev->bus->bridge));
	return is_card_dino(&dino_dev->hba.dev->id);
}