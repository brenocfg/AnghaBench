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
struct hfi1_pportdata {scalar_t__ neighbor_fm_security; scalar_t__ neighbor_type; scalar_t__ neighbor_port_number; scalar_t__ neighbor_guid; } ;

/* Variables and functions */

__attribute__((used)) static void reset_neighbor_info(struct hfi1_pportdata *ppd)
{
	ppd->neighbor_guid = 0;
	ppd->neighbor_port_number = 0;
	ppd->neighbor_type = 0;
	ppd->neighbor_fm_security = 0;
}