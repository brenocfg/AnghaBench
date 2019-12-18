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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ longccb; } ;
struct dax_ccb {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dax_dbg (char*,...) ; 

__attribute__((used)) static void dax_prt_ccbs(struct dax_ccb *ccb, int nelem)
{
	int i, j;
	u64 *ccbp;

	dax_dbg("ccb buffer:");
	for (i = 0; i < nelem; i++) {
		ccbp = (u64 *)&ccb[i];
		dax_dbg(" %sccb[%d]", ccb[i].hdr.longccb ? "long " : "",  i);
		for (j = 0; j < 8; j++)
			dax_dbg("\tccb[%d].dwords[%d]=0x%llx",
				i, j, *(ccbp + j));
	}
}