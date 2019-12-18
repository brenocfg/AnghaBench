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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct SMap2 {scalar_t__ m_Frequency; int /*<<< orphan*/  m_Param2; int /*<<< orphan*/  m_Param1; } ;

/* Variables and functions */

__attribute__((used)) static bool SearchMap3(struct SMap2 Map[], u32 Frequency,
		       u8 *pParam1, u8 *pParam2)
{
	int i = 0;

	while ((Map[i].m_Frequency != 0) &&
	       (Frequency > Map[i].m_Frequency))
		i += 1;
	if (Map[i].m_Frequency == 0)
		return false;
	*pParam1 = Map[i].m_Param1;
	*pParam2 = Map[i].m_Param2;
	return true;
}