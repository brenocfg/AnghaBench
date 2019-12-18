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
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int mvebu_comphy_get_mode (int,int,int,int,int) ; 

__attribute__((used)) static inline int mvebu_comphy_get_fw_mode(int lane, int port,
					   enum phy_mode mode, int submode)
{
	return mvebu_comphy_get_mode(true, lane, port, mode, submode);
}