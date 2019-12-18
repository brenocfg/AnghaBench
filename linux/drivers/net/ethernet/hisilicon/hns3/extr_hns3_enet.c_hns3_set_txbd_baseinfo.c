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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_TXD_FE_B ; 
 int /*<<< orphan*/  HNS3_TXD_VLD_B ; 
 int /*<<< orphan*/  hns3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hns3_set_txbd_baseinfo(u16 *bdtp_fe_sc_vld_ra_ri, int frag_end)
{
	/* Config bd buffer end */
	if (!!frag_end)
		hns3_set_field(*bdtp_fe_sc_vld_ra_ri, HNS3_TXD_FE_B, 1U);
	hns3_set_field(*bdtp_fe_sc_vld_ra_ri, HNS3_TXD_VLD_B, 1U);
}