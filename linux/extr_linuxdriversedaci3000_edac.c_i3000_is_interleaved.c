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
 int I3000_RANKS_PER_CHANNEL ; 
 scalar_t__ even_rank_attrib (unsigned char const) ; 
 scalar_t__ odd_rank_attrib (unsigned char const) ; 

__attribute__((used)) static int i3000_is_interleaved(const unsigned char *c0dra,
				const unsigned char *c1dra,
				const unsigned char *c0drb,
				const unsigned char *c1drb)
{
	int i;

	/*
	 * If the channels aren't populated identically then
	 * we're not interleaved.
	 */
	for (i = 0; i < I3000_RANKS_PER_CHANNEL / 2; i++)
		if (odd_rank_attrib(c0dra[i]) != odd_rank_attrib(c1dra[i]) ||
			even_rank_attrib(c0dra[i]) !=
						even_rank_attrib(c1dra[i]))
			return 0;

	/*
	 * If the rank boundaries for the two channels are different
	 * then we're not interleaved.
	 */
	for (i = 0; i < I3000_RANKS_PER_CHANNEL; i++)
		if (c0drb[i] != c1drb[i])
			return 0;

	return 1;
}