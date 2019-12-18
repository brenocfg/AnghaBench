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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFLP_CFG_1 ; 
 int /*<<< orphan*/  FFLP_CFG_1_LLCSNAP ; 
 int /*<<< orphan*/  nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fflp_llcsnap_enable(struct niu *np, int on)
{
	u64 val = nr64(FFLP_CFG_1);

	if (on)
		val |= FFLP_CFG_1_LLCSNAP;
	else
		val &= ~FFLP_CFG_1_LLCSNAP;
	nw64(FFLP_CFG_1, val);
}