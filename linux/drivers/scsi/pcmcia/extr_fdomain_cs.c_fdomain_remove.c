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
struct pcmcia_device {TYPE_1__** resource; int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDOMAIN_REGION_SIZE ; 
 int /*<<< orphan*/  fdomain_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdomain_remove(struct pcmcia_device *link)
{
	fdomain_destroy(link->priv);
	release_region(link->resource[0]->start, FDOMAIN_REGION_SIZE);
	pcmcia_disable_device(link);
}