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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * membuf_message ; 

__attribute__((used)) static void do_membuf_error(u8 errors)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (errors & (1 << i))
			e752x_printk(KERN_WARNING, "Non-Fatal Error %s\n",
				membuf_message[i]);
	}
}