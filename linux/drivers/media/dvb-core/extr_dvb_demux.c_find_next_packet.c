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

__attribute__((used)) static inline int find_next_packet(const u8 *buf, int pos, size_t count,
				   const int pktsize)
{
	int start = pos, lost;

	while (pos < count) {
		if (buf[pos] == 0x47 ||
		    (pktsize == 204 && buf[pos] == 0xB8))
			break;
		pos++;
	}

	lost = pos - start;
	if (lost) {
		/* This garbage is part of a valid packet? */
		int backtrack = pos - pktsize;
		if (backtrack >= 0 && (buf[backtrack] == 0x47 ||
		    (pktsize == 204 && buf[backtrack] == 0xB8)))
			return backtrack;
	}

	return pos;
}