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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFLP_CFG_1 ; 
 int FFLP_CFG_1_FCRAMOUTDR_NORMAL ; 
 int FFLP_CFG_1_FFLPINITDONE ; 
 int FFLP_CFG_1_PIO_FIO_RST ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fflp_reset(struct niu *np)
{
	u64 val;

	nw64(FFLP_CFG_1, FFLP_CFG_1_PIO_FIO_RST);
	udelay(10);
	nw64(FFLP_CFG_1, 0);

	val = FFLP_CFG_1_FCRAMOUTDR_NORMAL | FFLP_CFG_1_FFLPINITDONE;
	nw64(FFLP_CFG_1, val);
}