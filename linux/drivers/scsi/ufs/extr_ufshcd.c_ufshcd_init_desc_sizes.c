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
struct TYPE_2__ {int /*<<< orphan*/  hlth_desc; int /*<<< orphan*/  geom_desc; int /*<<< orphan*/  unit_desc; int /*<<< orphan*/  conf_desc; int /*<<< orphan*/  interc_desc; int /*<<< orphan*/  pwr_desc; int /*<<< orphan*/  dev_desc; } ;
struct ufs_hba {TYPE_1__ desc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_DESC_CONFIGURATION_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_DEVICE_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_GEOMETRY_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_HEALTH_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_CONFIGURATION ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_DEVICE ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_GEOMETRY ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_HEALTH ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_INTERCONNECT ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_POWER ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_UNIT ; 
 int /*<<< orphan*/  QUERY_DESC_INTERCONNECT_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_POWER_DEF_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_UNIT_DEF_SIZE ; 
 int ufshcd_read_desc_length (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ufshcd_init_desc_sizes(struct ufs_hba *hba)
{
	int err;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_DEVICE, 0,
		&hba->desc_size.dev_desc);
	if (err)
		hba->desc_size.dev_desc = QUERY_DESC_DEVICE_DEF_SIZE;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_POWER, 0,
		&hba->desc_size.pwr_desc);
	if (err)
		hba->desc_size.pwr_desc = QUERY_DESC_POWER_DEF_SIZE;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_INTERCONNECT, 0,
		&hba->desc_size.interc_desc);
	if (err)
		hba->desc_size.interc_desc = QUERY_DESC_INTERCONNECT_DEF_SIZE;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_CONFIGURATION, 0,
		&hba->desc_size.conf_desc);
	if (err)
		hba->desc_size.conf_desc = QUERY_DESC_CONFIGURATION_DEF_SIZE;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_UNIT, 0,
		&hba->desc_size.unit_desc);
	if (err)
		hba->desc_size.unit_desc = QUERY_DESC_UNIT_DEF_SIZE;

	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_GEOMETRY, 0,
		&hba->desc_size.geom_desc);
	if (err)
		hba->desc_size.geom_desc = QUERY_DESC_GEOMETRY_DEF_SIZE;
	err = ufshcd_read_desc_length(hba, QUERY_DESC_IDN_HEALTH, 0,
		&hba->desc_size.hlth_desc);
	if (err)
		hba->desc_size.hlth_desc = QUERY_DESC_HEALTH_DEF_SIZE;
}