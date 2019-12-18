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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct kvaser_pciefd_can {TYPE_1__ can; scalar_t__ reg_base; } ;
struct kvaser_pciefd {int nr_channels; struct kvaser_pciefd_can** can; } ;

/* Variables and functions */
 scalar_t__ KVASER_PCIEFD_KCAN_IEN_REG ; 
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_pwm_stop (struct kvaser_pciefd_can*) ; 

__attribute__((used)) static void kvaser_pciefd_teardown_can_ctrls(struct kvaser_pciefd *pcie)
{
	int i;
	struct kvaser_pciefd_can *can;

	for (i = 0; i < pcie->nr_channels; i++) {
		can = pcie->can[i];
		if (can) {
			iowrite32(0,
				  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
			kvaser_pciefd_pwm_stop(can);
			free_candev(can->can.dev);
		}
	}
}