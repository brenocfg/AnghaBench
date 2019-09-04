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
struct vpdma_data {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  VPDMA_LIST_STAT_SYNC ; 
 int read_reg (struct vpdma_data*,int /*<<< orphan*/ ) ; 

bool vpdma_list_busy(struct vpdma_data *vpdma, int list_num)
{
	return read_reg(vpdma, VPDMA_LIST_STAT_SYNC) & BIT(list_num + 16);
}