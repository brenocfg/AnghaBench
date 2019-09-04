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
struct dsaf_tbl_line_cfg {int dummy; } ;
struct dsaf_device {int /*<<< orphan*/  tcam_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_dsaf_tbl_line_addr_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_line_cfg (struct dsaf_device*,struct dsaf_tbl_line_cfg*) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_line_pul (struct dsaf_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_dsaf_single_line_tbl_cfg(
	struct dsaf_device *dsaf_dev,
	u32 address, struct dsaf_tbl_line_cfg *ptbl_line)
{
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_line_addr_cfg(dsaf_dev, address);

	/*Write Line*/
	hns_dsaf_tbl_line_cfg(dsaf_dev, ptbl_line);

	/*Write Plus*/
	hns_dsaf_tbl_line_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
}