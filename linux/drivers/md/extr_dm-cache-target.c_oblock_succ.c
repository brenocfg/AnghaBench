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
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 scalar_t__ from_oblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_oblock (scalar_t__) ; 

__attribute__((used)) static inline dm_oblock_t oblock_succ(dm_oblock_t b)
{
	return to_oblock(from_oblock(b) + 1ull);
}