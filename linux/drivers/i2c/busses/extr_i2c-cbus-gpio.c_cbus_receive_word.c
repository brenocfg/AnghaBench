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
struct cbus_host {int dummy; } ;

/* Variables and functions */
 int cbus_receive_bit (struct cbus_host*) ; 

__attribute__((used)) static int cbus_receive_word(struct cbus_host *host)
{
	int ret = 0;
	int i;

	for (i = 16; i > 0; i--) {
		int bit = cbus_receive_bit(host);

		if (bit < 0)
			return bit;

		if (bit)
			ret |= 1 << (i - 1);
	}
	return ret;
}