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
struct mvneta_port {int /*<<< orphan*/  phylink; } ;

/* Variables and functions */
 int MVNETA_GMAC_LINK_UP ; 
 int /*<<< orphan*/  MVNETA_GMAC_STATUS ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_mac_change (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_link_change(struct mvneta_port *pp)
{
	u32 gmac_stat = mvreg_read(pp, MVNETA_GMAC_STATUS);

	phylink_mac_change(pp->phylink, !!(gmac_stat & MVNETA_GMAC_LINK_UP));
}