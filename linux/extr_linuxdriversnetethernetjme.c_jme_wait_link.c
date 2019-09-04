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
typedef  int u32 ;
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int JME_WAIT_LINK_TIME ; 
 int PHY_LINK_UP ; 
 int jme_linkstat_from_phy (struct jme_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void
jme_wait_link(struct jme_adapter *jme)
{
	u32 phylink, to = JME_WAIT_LINK_TIME;

	msleep(1000);
	phylink = jme_linkstat_from_phy(jme);
	while (!(phylink & PHY_LINK_UP) && (to -= 10) > 0) {
		usleep_range(10000, 11000);
		phylink = jme_linkstat_from_phy(jme);
	}
}