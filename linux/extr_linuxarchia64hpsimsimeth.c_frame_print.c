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

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
frame_print(unsigned char *from, unsigned char *frame, int len)
{
	int i;

	printk("%s: (%d) %02x", from, len, frame[0] & 0xff);
	for(i=1; i < 6; i++ ) {
		printk(":%02x", frame[i] &0xff);
	}
	printk(" %2x", frame[6] &0xff);
	for(i=7; i < 12; i++ ) {
		printk(":%02x", frame[i] &0xff);
	}
	printk(" [%02x%02x]\n", frame[12], frame[13]);

	for(i=14; i < len; i++ ) {
		printk("%02x ", frame[i] &0xff);
		if ( (i%10)==0) printk("\n");
	}
	printk("\n");
}