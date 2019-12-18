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
struct serial_info {unsigned int c950ctrl; } ;
struct pcmcia_device {struct serial_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 

__attribute__((used)) static void quirk_wakeup_possio_gcc(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	unsigned int ctrl = info->c950ctrl;

	outb(0xA, ctrl + 1);
	msleep(100);
	outb(0xE, ctrl + 1);
	msleep(300);
	outb(0xC, ctrl + 1);
	msleep(100);
	outb(0xE, ctrl + 1);
	msleep(200);
	outb(0xF, ctrl + 1);
	msleep(100);
	outb(0xE, ctrl + 1);
	msleep(100);
	outb(0xC, ctrl + 1);
}