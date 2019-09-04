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
 unsigned long REMOTE_HUB_L (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH1_SHUB_ID ; 
 unsigned long SH1_SHUB_ID_REVISION_MASK ; 
 unsigned long SH1_SHUB_ID_REVISION_SHFT ; 
 scalar_t__ is_shub2 () ; 

__attribute__((used)) static inline int is_shub_1_1(int nasid)
{
	unsigned long id;
	int rev;

	if (is_shub2())
		return 0;
	id = REMOTE_HUB_L(nasid, SH1_SHUB_ID);
	rev = (id & SH1_SHUB_ID_REVISION_MASK) >> SH1_SHUB_ID_REVISION_SHFT;
	return rev <= 2;
}