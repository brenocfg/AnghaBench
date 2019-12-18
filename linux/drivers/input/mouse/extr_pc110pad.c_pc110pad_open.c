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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PC110PAD_ON ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pc110pad_count ; 
 int /*<<< orphan*/  pc110pad_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pc110pad_io ; 

__attribute__((used)) static int pc110pad_open(struct input_dev *dev)
{
	pc110pad_interrupt(0, NULL);
	pc110pad_interrupt(0, NULL);
	pc110pad_interrupt(0, NULL);
	outb(PC110PAD_ON, pc110pad_io + 2);
	pc110pad_count = 0;

	return 0;
}