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
typedef  int uint32_t ;
struct sm_oob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct sm_oob*,int const*,int) ; 

__attribute__((used)) static inline int sm_block_erased(struct sm_oob *oob)
{
	static const uint32_t erased_pattern[4] = {
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	/* First test for erased block */
	if (!memcmp(oob, erased_pattern, sizeof(*oob)))
		return 1;
	return 0;
}