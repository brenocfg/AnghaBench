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
struct pcmcia_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  ide_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  ide_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_detach(struct pcmcia_device *link)
{
    ide_info_t *info = link->priv;

    dev_dbg(&link->dev, "ide_detach(0x%p)\n", link);

    ide_release(link);

    kfree(info);
}