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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;
struct TYPE_4__ {TYPE_1__ tx_sc; } ;
struct macsec_dev {TYPE_2__ secy; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 

__attribute__((used)) static void macsec_free_netdev(struct net_device *dev)
{
	struct macsec_dev *macsec = macsec_priv(dev);

	free_percpu(macsec->stats);
	free_percpu(macsec->secy.tx_sc.stats);

}