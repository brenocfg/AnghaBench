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
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cblock (scalar_t__) ; 

__attribute__((used)) static inline dm_cblock_t cblock_succ(dm_cblock_t b)
{
	return to_cblock(from_cblock(b) + 1);
}