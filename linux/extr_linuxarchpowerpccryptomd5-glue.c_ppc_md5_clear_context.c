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
typedef  int /*<<< orphan*/  u32 ;
struct md5_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline void ppc_md5_clear_context(struct md5_state *sctx)
{
	int count = sizeof(struct md5_state) >> 2;
	u32 *ptr = (u32 *)sctx;

	/* make sure we can clear the fast way */
	BUILD_BUG_ON(sizeof(struct md5_state) % 4);
	do { *ptr++ = 0; } while (--count);
}