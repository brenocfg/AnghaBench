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
struct radio_isa_card {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtrack_initialize(struct radio_isa_card *isa)
{
	/* this ensures that the volume is all the way up  */
	outb(0x90, isa->io);	/* volume up but still "on"	*/
	msleep(3000);		/* make sure it's totally up	*/
	outb(0xc0, isa->io);	/* steady volume, mute card	*/
	return 0;
}