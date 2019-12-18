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
typedef  int u32 ;
struct mtd_info {int dummy; } ;
struct fsl_ifc_ctrl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int check_read_ecc(struct mtd_info *mtd, struct fsl_ifc_ctrl *ctrl,
			  u32 eccstat, unsigned int bufnum)
{
	return  (eccstat >> ((3 - bufnum % 4) * 8)) & 15;
}