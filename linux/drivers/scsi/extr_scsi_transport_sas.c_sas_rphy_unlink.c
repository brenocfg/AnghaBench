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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct sas_rphy {TYPE_1__ dev; } ;
struct sas_port {int /*<<< orphan*/ * rphy; } ;

/* Variables and functions */
 struct sas_port* dev_to_sas_port (int /*<<< orphan*/ ) ; 

void sas_rphy_unlink(struct sas_rphy *rphy)
{
	struct sas_port *parent = dev_to_sas_port(rphy->dev.parent);

	parent->rphy = NULL;
}