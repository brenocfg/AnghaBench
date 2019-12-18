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
struct edp_aux {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  EDP_AUX_CTRL_ENABLE ; 
 int /*<<< orphan*/  EDP_AUX_CTRL_RESET ; 
 scalar_t__ REG_EDP_AUX_CTRL ; 
 int /*<<< orphan*/  edp_read (scalar_t__) ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

void msm_edp_aux_ctrl(struct edp_aux *aux, int enable)
{
	u32 data;

	DBG("enable=%d", enable);
	data = edp_read(aux->base + REG_EDP_AUX_CTRL);

	if (enable) {
		data |= EDP_AUX_CTRL_RESET;
		edp_write(aux->base + REG_EDP_AUX_CTRL, data);
		/* Make sure full reset */
		wmb();
		usleep_range(500, 1000);

		data &= ~EDP_AUX_CTRL_RESET;
		data |= EDP_AUX_CTRL_ENABLE;
		edp_write(aux->base + REG_EDP_AUX_CTRL, data);
	} else {
		data &= ~EDP_AUX_CTRL_ENABLE;
		edp_write(aux->base + REG_EDP_AUX_CTRL, data);
	}
}