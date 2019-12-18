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
struct net_device {int dummy; } ;
struct board_info {int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct board_info* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_nway_reset(struct net_device *dev)
{
	struct board_info *dm = to_dm9000_board(dev);
	return mii_nway_restart(&dm->mii);
}