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
struct serial_info {int dummy; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; struct serial_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct serial_info*) ; 
 int /*<<< orphan*/  serial_remove (struct pcmcia_device*) ; 

__attribute__((used)) static void serial_detach(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;

	dev_dbg(&link->dev, "serial_detach\n");

	/*
	 * Ensure that the ports have been released.
	 */
	serial_remove(link);

	/* free bits */
	kfree(info);
}