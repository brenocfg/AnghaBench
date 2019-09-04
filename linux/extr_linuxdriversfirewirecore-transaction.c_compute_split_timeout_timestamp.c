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
typedef  int u32 ;
struct fw_card {unsigned int split_timeout_cycles; } ;

/* Variables and functions */

__attribute__((used)) static u32 compute_split_timeout_timestamp(struct fw_card *card,
					   u32 request_timestamp)
{
	unsigned int cycles;
	u32 timestamp;

	cycles = card->split_timeout_cycles;
	cycles += request_timestamp & 0x1fff;

	timestamp = request_timestamp & ~0x1fff;
	timestamp += (cycles / 8000) << 13;
	timestamp |= cycles % 8000;

	return timestamp;
}