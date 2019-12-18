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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_config_endianity (struct bnx2x*,int) ; 

__attribute__((used)) static void bnx2x_set_endianity(struct bnx2x *bp)
{
#ifdef __BIG_ENDIAN
	bnx2x_config_endianity(bp, 1);
#else
	bnx2x_config_endianity(bp, 0);
#endif
}