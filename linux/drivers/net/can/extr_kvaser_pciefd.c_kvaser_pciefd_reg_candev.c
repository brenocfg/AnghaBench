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
struct kvaser_pciefd {int nr_channels; TYPE_2__** can; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ can; } ;

/* Variables and functions */
 int register_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_pciefd_reg_candev(struct kvaser_pciefd *pcie)
{
	int i;

	for (i = 0; i < pcie->nr_channels; i++) {
		int err = register_candev(pcie->can[i]->can.dev);

		if (err) {
			int j;

			/* Unregister all successfully registered devices. */
			for (j = 0; j < i; j++)
				unregister_candev(pcie->can[j]->can.dev);
			return err;
		}
	}

	return 0;
}