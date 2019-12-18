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
struct net_device {int /*<<< orphan*/  tstats; } ;
struct macsec_dev {int /*<<< orphan*/  gro_cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gro_cells_destroy (int /*<<< orphan*/ *) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 

__attribute__((used)) static void macsec_dev_uninit(struct net_device *dev)
{
	struct macsec_dev *macsec = macsec_priv(dev);

	gro_cells_destroy(&macsec->gro_cells);
	free_percpu(dev->tstats);
}