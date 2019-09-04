#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct cadet {int rdsstat; TYPE_1__ readtimer; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cadet_handler ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cadet_start_rds(struct cadet *dev)
{
	dev->rdsstat = 1;
	outb(0x80, dev->io);        /* Select RDS fifo */
	timer_setup(&dev->readtimer, cadet_handler, 0);
	dev->readtimer.expires = jiffies + msecs_to_jiffies(50);
	add_timer(&dev->readtimer);
}