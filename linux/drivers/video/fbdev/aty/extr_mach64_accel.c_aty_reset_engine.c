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
struct atyfb_par {scalar_t__ fifo_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CNTL ; 
 int BUS_FIFO_ERR_ACK ; 
 int BUS_HOST_ERR_ACK ; 
 int /*<<< orphan*/  GEN_TEST_CNTL ; 
 int GUI_ENGINE_ENABLE ; 
 int HWCURSOR_ENABLE ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 

void aty_reset_engine(struct atyfb_par *par)
{
	/* reset engine */
	aty_st_le32(GEN_TEST_CNTL,
		aty_ld_le32(GEN_TEST_CNTL, par) &
		~(GUI_ENGINE_ENABLE | HWCURSOR_ENABLE), par);
	/* enable engine */
	aty_st_le32(GEN_TEST_CNTL,
		aty_ld_le32(GEN_TEST_CNTL, par) | GUI_ENGINE_ENABLE, par);
	/* ensure engine is not locked up by clearing any FIFO or */
	/* HOST errors */
	aty_st_le32(BUS_CNTL,
		aty_ld_le32(BUS_CNTL, par) | BUS_HOST_ERR_ACK | BUS_FIFO_ERR_ACK, par);

	par->fifo_space = 0;
}