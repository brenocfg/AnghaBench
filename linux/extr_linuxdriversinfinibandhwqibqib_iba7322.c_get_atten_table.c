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
struct txdds_ent {int dummy; } ;

/* Variables and functions */
 unsigned int TXDDS_TABLE_SZ ; 

__attribute__((used)) static const struct txdds_ent *get_atten_table(const struct txdds_ent *txdds,
					       unsigned atten)
{
	/*
	 * The attenuation table starts at 2dB for entry 1,
	 * with entry 0 being the loopback entry.
	 */
	if (atten <= 2)
		atten = 1;
	else if (atten > TXDDS_TABLE_SZ)
		atten = TXDDS_TABLE_SZ - 1;
	else
		atten--;
	return txdds + atten;
}