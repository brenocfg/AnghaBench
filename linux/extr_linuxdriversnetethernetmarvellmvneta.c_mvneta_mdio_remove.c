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
struct mvneta_port {int /*<<< orphan*/  phylink; } ;

/* Variables and functions */
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_mdio_remove(struct mvneta_port *pp)
{
	phylink_disconnect_phy(pp->phylink);
}