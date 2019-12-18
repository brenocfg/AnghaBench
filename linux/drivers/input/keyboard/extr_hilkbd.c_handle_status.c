#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int curdev; scalar_t__ ptr; } ;

/* Variables and functions */
 TYPE_1__ hil_dev ; 
 int /*<<< orphan*/  poll_finished () ; 

__attribute__((used)) static inline void handle_status(unsigned char s, unsigned char c)
{
	if (c & 0x8) {
		/* End of block */
		if (c & 0x10)
			poll_finished();
	} else {
		if (c & 0x10) {
			if (hil_dev.curdev)
				poll_finished();  /* just in case */
			hil_dev.curdev = c & 7;
			hil_dev.ptr = 0;
		}
	}
}