#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int packet; } ;
struct hilse_node {int act; int /*<<< orphan*/  arg; TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  hil_packet ;
struct TYPE_5__ {int imatch; int istarted; int icount; int /*<<< orphan*/  isem; int /*<<< orphan*/  ipacket; int /*<<< orphan*/  instart; int /*<<< orphan*/  intimeout; int /*<<< orphan*/  ddi; } ;
typedef  TYPE_2__ hil_mlc ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
#define  HILSE_EXPECT 131 
#define  HILSE_EXPECT_DISC 130 
#define  HILSE_EXPECT_LAST 129 
#define  HILSE_IN 128 
 int HIL_PKT_ADDR_SHIFT ; 
 int /*<<< orphan*/  down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hilse_setup_input(hil_mlc *mlc, const struct hilse_node *node)
{

	switch (node->act) {
	case HILSE_EXPECT_DISC:
		mlc->imatch = node->object.packet;
		mlc->imatch |= ((mlc->ddi + 2) << HIL_PKT_ADDR_SHIFT);
		break;
	case HILSE_EXPECT_LAST:
		mlc->imatch = node->object.packet;
		mlc->imatch |= ((mlc->ddi + 1) << HIL_PKT_ADDR_SHIFT);
		break;
	case HILSE_EXPECT:
		mlc->imatch = node->object.packet;
		break;
	case HILSE_IN:
		mlc->imatch = 0;
		break;
	default:
		BUG();
	}
	mlc->istarted = 1;
	mlc->intimeout = usecs_to_jiffies(node->arg);
	mlc->instart = jiffies;
	mlc->icount = 15;
	memset(mlc->ipacket, 0, 16 * sizeof(hil_packet));
	BUG_ON(down_trylock(&mlc->isem));
}