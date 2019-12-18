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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 void cxgb4_getpgtccfg (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cxgb4_getpgtccfg_tx(struct net_device *dev, int tc,
				u8 *prio_type, u8 *pgid, u8 *bw_per,
				u8 *up_tc_map)
{
	/* tc 0 is written at MSB position */
	return cxgb4_getpgtccfg(dev, (7 - tc), prio_type, pgid, bw_per,
				up_tc_map, 1);
}