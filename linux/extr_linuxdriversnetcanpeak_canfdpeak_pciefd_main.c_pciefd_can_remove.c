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
struct TYPE_2__ {int /*<<< orphan*/  ndev; } ;
struct pciefd_can {TYPE_1__ ucan; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciefd_can_remove(struct pciefd_can *priv)
{
	/* unregister (close) the can device to go back to RST mode first */
	unregister_candev(priv->ucan.ndev);

	/* finally, free the candev object */
	free_candev(priv->ucan.ndev);
}