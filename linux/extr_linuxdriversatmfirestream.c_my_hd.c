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

__attribute__((used)) static void my_hd (void *addr, int len)
{
	int j, ch;
	unsigned char *ptr = addr;

	while (len > 0) {
		printk ("%p ", ptr);
		for (j=0;j < ((len < 16)?len:16);j++) {
			printk ("%02x %s", ptr[j], (j==7)?" ":"");
		}
		for (  ;j < 16;j++) {
			printk ("   %s", (j==7)?" ":"");
		}
		for (j=0;j < ((len < 16)?len:16);j++) {
			ch = ptr[j];
			printk ("%c", (ch < 0x20)?'.':((ch > 0x7f)?'.':ch));
		}
		printk ("\n");
		ptr += 16;
		len -= 16;
	}
}