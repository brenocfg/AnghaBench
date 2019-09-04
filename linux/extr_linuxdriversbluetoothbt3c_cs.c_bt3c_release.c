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
struct pcmcia_device {struct bt3c_info* priv; } ;
struct bt3c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt3c_close (struct bt3c_info*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void bt3c_release(struct pcmcia_device *link)
{
	struct bt3c_info *info = link->priv;

	bt3c_close(info);

	pcmcia_disable_device(link);
}