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
struct pnp_dev {int dummy; } ;
struct ide_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_host_remove (struct ide_host*) ; 
 struct ide_host* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_port_start (struct pnp_dev*,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void idepnp_remove(struct pnp_dev *dev)
{
	struct ide_host *host = pnp_get_drvdata(dev);

	ide_host_remove(host);

	release_region(pnp_port_start(dev, 1), 1);
	release_region(pnp_port_start(dev, 0), 8);
}