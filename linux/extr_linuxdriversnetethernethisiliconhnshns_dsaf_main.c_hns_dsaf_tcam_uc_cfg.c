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
struct dsaf_tbl_tcam_ucast_cfg {int dummy; } ;
struct dsaf_tbl_tcam_data {int dummy; } ;
struct dsaf_device {int /*<<< orphan*/  tcam_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_addr_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_data_cfg (struct dsaf_device*,struct dsaf_tbl_tcam_data*) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_data_ucast_pul (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_ucast_cfg (struct dsaf_device*,struct dsaf_tbl_tcam_ucast_cfg*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_dsaf_tcam_uc_cfg(
	struct dsaf_device *dsaf_dev, u32 address,
	struct dsaf_tbl_tcam_data *ptbl_tcam_data,
	struct dsaf_tbl_tcam_ucast_cfg *ptbl_tcam_ucast)
{
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);
	/*Write Tcam Data*/
	hns_dsaf_tbl_tcam_data_cfg(dsaf_dev, ptbl_tcam_data);
	/*Write Tcam Ucast*/
	hns_dsaf_tbl_tcam_ucast_cfg(dsaf_dev, ptbl_tcam_ucast);
	/*Write Plus*/
	hns_dsaf_tbl_tcam_data_ucast_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
}