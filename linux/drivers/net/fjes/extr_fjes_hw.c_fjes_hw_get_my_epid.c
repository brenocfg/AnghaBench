#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int epid; } ;
union REG_OWNER_EPID {TYPE_1__ bits; int /*<<< orphan*/  reg; } ;
struct fjes_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSCT_OWNER_EPID ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fjes_hw_get_my_epid(struct fjes_hw *hw)
{
	union REG_OWNER_EPID info;

	info.reg = rd32(XSCT_OWNER_EPID);

	return info.bits.epid;
}