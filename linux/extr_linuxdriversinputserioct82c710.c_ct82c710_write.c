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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT82C710_DATA ; 
 scalar_t__ ct82c170_wait () ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct82c710_write(struct serio *port, unsigned char c)
{
	if (ct82c170_wait()) return -1;
	outb_p(c, CT82C710_DATA);
	return 0;
}