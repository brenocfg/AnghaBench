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
struct cxl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_TB_CTLSTAT ; 
 int PSL_2048_250MHZ_CYCLES ; 
 int /*<<< orphan*/  TBSYNC_CNT (int) ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_timebase_ctrl_psl8(struct cxl *adapter)
{
	cxl_p1_write(adapter, CXL_PSL_TB_CTLSTAT,
		     TBSYNC_CNT(2 * PSL_2048_250MHZ_CYCLES));
}