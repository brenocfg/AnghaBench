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
typedef  scalar_t__ range_action ;

/* Variables and functions */
 unsigned int __MAX_SUBCHANNEL ; 
 scalar_t__ add ; 
 int /*<<< orphan*/ * bl_dev ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blacklist_range(range_action action, unsigned int from_ssid,
			   unsigned int to_ssid, unsigned int from,
			   unsigned int to, int msgtrigger)
{
	if ((from_ssid > to_ssid) || ((from_ssid == to_ssid) && (from > to))) {
		if (msgtrigger)
			pr_warn("0.%x.%04x to 0.%x.%04x is not a valid range for cio_ignore\n",
				from_ssid, from, to_ssid, to);

		return 1;
	}

	while ((from_ssid < to_ssid) || ((from_ssid == to_ssid) &&
	       (from <= to))) {
		if (action == add)
			set_bit(from, bl_dev[from_ssid]);
		else
			clear_bit(from, bl_dev[from_ssid]);
		from++;
		if (from > __MAX_SUBCHANNEL) {
			from_ssid++;
			from = 0;
		}
	}

	return 0;
}