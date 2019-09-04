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
typedef  scalar_t__ u32 ;
struct SRFBandMap {scalar_t__ m_RF_max; } ;

/* Variables and functions */

__attribute__((used)) static bool SearchMap4(struct SRFBandMap Map[],
		       u32 Frequency, u8 *pRFBand)
{
	int i = 0;

	while (i < 7 && (Frequency > Map[i].m_RF_max))
		i += 1;
	if (i == 7)
		return false;
	*pRFBand = i;
	return true;
}