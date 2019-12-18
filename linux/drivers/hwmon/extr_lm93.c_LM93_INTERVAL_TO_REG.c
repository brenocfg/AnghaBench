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

/* Variables and functions */
 long* lm93_interval_map ; 

__attribute__((used)) static u8 LM93_INTERVAL_TO_REG(long interval)
{
	int i;
	for (i = 0; i < 9; i++)
		if (interval <= lm93_interval_map[i])
			break;

	/* can fall through with i==9 */
	return (u8)i;
}