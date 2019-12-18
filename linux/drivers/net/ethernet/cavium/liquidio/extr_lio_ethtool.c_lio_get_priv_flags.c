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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct lio {TYPE_1__* oct_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 

__attribute__((used)) static u32 lio_get_priv_flags(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);

	return lio->oct_dev->priv_flags;
}