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
struct ltr501_data {int als_contr; int ps_contr; TYPE_1__* chip_info; } ;
struct TYPE_2__ {int als_mode_active; } ;

/* Variables and functions */
 int LTR501_CONTR_ACTIVE ; 
 int ltr501_write_contr (struct ltr501_data*,int,int) ; 

__attribute__((used)) static int ltr501_powerdown(struct ltr501_data *data)
{
	return ltr501_write_contr(data, data->als_contr &
				  ~data->chip_info->als_mode_active,
				  data->ps_contr & ~LTR501_CONTR_ACTIVE);
}