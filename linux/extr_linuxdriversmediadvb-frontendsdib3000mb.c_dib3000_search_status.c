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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  deb_srch (char*) ; 

__attribute__((used)) static int dib3000_search_status(u16 irq,u16 lock)
{
	if (irq & 0x02) {
		if (lock & 0x01) {
			deb_srch("auto search succeeded\n");
			return 1; // auto search succeeded
		} else {
			deb_srch("auto search not successful\n");
			return 0; // auto search failed
		}
	} else if (irq & 0x01)  {
		deb_srch("auto search failed\n");
		return 0; // auto search failed
	}
	return -1; // try again
}