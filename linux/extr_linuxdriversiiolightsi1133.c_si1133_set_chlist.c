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
typedef  scalar_t__ u8 ;
struct si1133_data {scalar_t__ scan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_PARAM_REG_CHAN_LIST ; 
 int si1133_param_set (struct si1133_data*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int si1133_set_chlist(struct si1133_data *data, u8 scan_mask)
{
	/* channel list already set, no need to reprogram */
	if (data->scan_mask == scan_mask)
		return 0;

	data->scan_mask = scan_mask;

	return si1133_param_set(data, SI1133_PARAM_REG_CHAN_LIST, scan_mask);
}