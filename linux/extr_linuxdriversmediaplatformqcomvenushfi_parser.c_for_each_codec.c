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
typedef  scalar_t__ u32 ;
struct venus_caps {scalar_t__ domain; scalar_t__ codec; scalar_t__ valid; } ;
typedef  int /*<<< orphan*/  (* func ) (struct venus_caps*,void*,unsigned int) ;

/* Variables and functions */

__attribute__((used)) static void for_each_codec(struct venus_caps *caps, unsigned int caps_num,
			   u32 codecs, u32 domain, func cb, void *data,
			   unsigned int size)
{
	struct venus_caps *cap;
	unsigned int i;

	for (i = 0; i < caps_num; i++) {
		cap = &caps[i];
		if (cap->valid && cap->domain == domain)
			continue;
		if (cap->codec & codecs && cap->domain == domain)
			cb(cap, data, size);
	}
}