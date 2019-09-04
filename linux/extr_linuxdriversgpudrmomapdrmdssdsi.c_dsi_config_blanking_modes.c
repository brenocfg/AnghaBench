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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int blanking_mode; int hfp_blanking_mode; int hbp_blanking_mode; int hsa_blanking_mode; } ;
struct dsi_data {TYPE_1__ vm_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CTRL ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_config_blanking_modes(struct dsi_data *dsi)
{
	int blanking_mode = dsi->vm_timings.blanking_mode;
	int hfp_blanking_mode = dsi->vm_timings.hfp_blanking_mode;
	int hbp_blanking_mode = dsi->vm_timings.hbp_blanking_mode;
	int hsa_blanking_mode = dsi->vm_timings.hsa_blanking_mode;
	u32 r;

	/*
	 * 0 = TX FIFO packets sent or LPS in corresponding blanking periods
	 * 1 = Long blanking packets are sent in corresponding blanking periods
	 */
	r = dsi_read_reg(dsi, DSI_CTRL);
	r = FLD_MOD(r, blanking_mode, 20, 20);		/* BLANKING_MODE */
	r = FLD_MOD(r, hfp_blanking_mode, 21, 21);	/* HFP_BLANKING */
	r = FLD_MOD(r, hbp_blanking_mode, 22, 22);	/* HBP_BLANKING */
	r = FLD_MOD(r, hsa_blanking_mode, 23, 23);	/* HSA_BLANKING */
	dsi_write_reg(dsi, DSI_CTRL, r);
}