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
struct vpdma_data {int dummy; } ;
typedef  enum vpdma_channel { ____Placeholder_vpdma_channel } vpdma_channel ;
struct TYPE_2__ {int cstat_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPDMA_CSTAT_LINE_MODE_MASK ; 
 int /*<<< orphan*/  VPDMA_CSTAT_LINE_MODE_SHIFT ; 
 TYPE_1__* chan_info ; 
 int /*<<< orphan*/  write_field_reg (struct vpdma_data*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vpdma_set_line_mode(struct vpdma_data *vpdma, int line_mode,
		enum vpdma_channel chan)
{
	int client_cstat = chan_info[chan].cstat_offset;

	write_field_reg(vpdma, client_cstat, line_mode,
		VPDMA_CSTAT_LINE_MODE_MASK, VPDMA_CSTAT_LINE_MODE_SHIFT);
}