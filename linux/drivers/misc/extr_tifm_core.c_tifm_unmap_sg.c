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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct tifm_dev {TYPE_1__ dev; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

void tifm_unmap_sg(struct tifm_dev *sock, struct scatterlist *sg, int nents,
		   int direction)
{
	pci_unmap_sg(to_pci_dev(sock->dev.parent), sg, nents, direction);
}