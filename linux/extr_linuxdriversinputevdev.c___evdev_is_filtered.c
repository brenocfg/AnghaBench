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
struct evdev_client {unsigned long** evmasks; } ;

/* Variables and functions */
 unsigned int EV_CNT ; 
 unsigned int EV_SYN ; 
 size_t evdev_get_mask_cnt (unsigned int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static bool __evdev_is_filtered(struct evdev_client *client,
				unsigned int type,
				unsigned int code)
{
	unsigned long *mask;
	size_t cnt;

	/* EV_SYN and unknown codes are never filtered */
	if (type == EV_SYN || type >= EV_CNT)
		return false;

	/* first test whether the type is filtered */
	mask = client->evmasks[0];
	if (mask && !test_bit(type, mask))
		return true;

	/* unknown values are never filtered */
	cnt = evdev_get_mask_cnt(type);
	if (!cnt || code >= cnt)
		return false;

	mask = client->evmasks[type];
	return mask && !test_bit(code, mask);
}