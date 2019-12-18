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
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_pfc_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_pg_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_tc_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_vport_info_update (struct hclge_dev*) ; 

__attribute__((used)) static void hclge_tm_schd_info_init(struct hclge_dev *hdev)
{
	hclge_tm_pg_info_init(hdev);

	hclge_tm_tc_info_init(hdev);

	hclge_tm_vport_info_update(hdev);

	hclge_pfc_info_init(hdev);
}