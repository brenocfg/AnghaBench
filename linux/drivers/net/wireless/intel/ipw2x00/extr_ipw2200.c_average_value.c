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
struct average {int pos; int sum; int /*<<< orphan*/  init; } ;
typedef  int s16 ;

/* Variables and functions */
 int AVG_ENTRIES ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s16 average_value(struct average *avg)
{
	if (!unlikely(avg->init)) {
		if (avg->pos)
			return avg->sum / avg->pos;
		return 0;
	}

	return avg->sum / AVG_ENTRIES;
}