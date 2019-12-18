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
struct sm_oob {int /*<<< orphan*/  block_status; } ;

/* Variables and functions */
 int hweight16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sm_block_valid(struct sm_oob *oob)
{
	return hweight16(oob->block_status) >= 7;
}