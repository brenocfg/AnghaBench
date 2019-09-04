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
struct qlcnic_adapter {int dummy; } ;
struct qlc_83xx_poll {int /*<<< orphan*/  status; int /*<<< orphan*/  mask; } ;
struct qlc_83xx_entry_hdr {int count; scalar_t__ delay; } ;
struct qlc_83xx_entry {unsigned long arg1; unsigned long arg2; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,unsigned long,int*) ; 
 scalar_t__ qlcnic_83xx_poll_reg (struct qlcnic_adapter*,unsigned long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_83xx_poll_list(struct qlcnic_adapter *p_dev,
				  struct qlc_83xx_entry_hdr *p_hdr)
{
	long delay;
	struct qlc_83xx_entry *entry;
	struct qlc_83xx_poll *poll;
	int i, err = 0;
	unsigned long arg1, arg2;

	poll = (struct qlc_83xx_poll *)((char *)p_hdr +
					sizeof(struct qlc_83xx_entry_hdr));

	entry = (struct qlc_83xx_entry *)((char *)poll +
					  sizeof(struct qlc_83xx_poll));
	delay = (long)p_hdr->delay;

	if (!delay) {
		for (i = 0; i < p_hdr->count; i++, entry++)
			qlcnic_83xx_poll_reg(p_dev, entry->arg1,
					     delay, poll->mask,
					     poll->status);
	} else {
		for (i = 0; i < p_hdr->count; i++, entry++) {
			arg1 = entry->arg1;
			arg2 = entry->arg2;
			if (delay) {
				if (qlcnic_83xx_poll_reg(p_dev,
							 arg1, delay,
							 poll->mask,
							 poll->status)){
					QLCRD32(p_dev, arg1, &err);
					if (err == -EIO)
						return;
					QLCRD32(p_dev, arg2, &err);
					if (err == -EIO)
						return;
				}
			}
		}
	}
}