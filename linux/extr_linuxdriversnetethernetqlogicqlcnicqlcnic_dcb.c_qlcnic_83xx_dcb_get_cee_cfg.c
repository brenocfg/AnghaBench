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
struct qlcnic_dcb {int /*<<< orphan*/  adapter; scalar_t__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlcnic_dcb_data_cee_param_map (int /*<<< orphan*/ ) ; 
 int qlcnic_dcb_query_cee_param (struct qlcnic_dcb*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_83xx_dcb_get_cee_cfg(struct qlcnic_dcb *dcb)
{
	int err;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)dcb->param, 0);
	if (err)
		return err;

	qlcnic_dcb_data_cee_param_map(dcb->adapter);

	return err;
}