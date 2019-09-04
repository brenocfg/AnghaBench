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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int hclge_buffer_alloc (struct hclge_dev*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_pause_setup_hw (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_rss_indir_init_cfg (struct hclge_dev*) ; 
 int hclge_rss_init_hw (struct hclge_dev*) ; 
 int hclge_tm_map_cfg (struct hclge_dev*) ; 
 int hclge_tm_schd_mode_hw (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_map_update(struct hnae3_handle *h)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;
	int ret;

	ret = hclge_tm_map_cfg(hdev);
	if (ret)
		return ret;

	ret = hclge_tm_schd_mode_hw(hdev);
	if (ret)
		return ret;

	ret = hclge_pause_setup_hw(hdev);
	if (ret)
		return ret;

	ret = hclge_buffer_alloc(hdev);
	if (ret)
		return ret;

	hclge_rss_indir_init_cfg(hdev);

	return hclge_rss_init_hw(hdev);
}