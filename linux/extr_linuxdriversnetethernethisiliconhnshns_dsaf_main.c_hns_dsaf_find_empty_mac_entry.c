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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct dsaf_drv_soft_mac_tbl {scalar_t__ index; } ;
struct dsaf_drv_priv {struct dsaf_drv_soft_mac_tbl* soft_mac_tbl; } ;
struct dsaf_device {scalar_t__ tcam_max_num; } ;

/* Variables and functions */
 scalar_t__ DSAF_INVALID_ENTRY_IDX ; 
 scalar_t__ hns_dsaf_dev_priv (struct dsaf_device*) ; 

__attribute__((used)) static u16 hns_dsaf_find_empty_mac_entry(struct dsaf_device *dsaf_dev)
{
	struct dsaf_drv_priv *priv =
	    (struct dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	struct dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u32 i;

	soft_mac_entry = priv->soft_mac_tbl;
	for (i = 0; i < dsaf_dev->tcam_max_num; i++) {
		/* inv all entry */
		if (soft_mac_entry->index == DSAF_INVALID_ENTRY_IDX)
			/* return find result --soft index */
			return i;

		soft_mac_entry++;
	}
	return DSAF_INVALID_ENTRY_IDX;
}