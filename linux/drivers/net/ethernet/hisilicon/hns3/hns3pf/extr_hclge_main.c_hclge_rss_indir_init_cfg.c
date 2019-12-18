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
struct hclge_vport {int* rss_indirection_tbl; int alloc_rss_size; } ;
struct hclge_dev {int num_vmdq_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int HCLGE_RSS_IND_TBL_SIZE ; 

void hclge_rss_indir_init_cfg(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	int i, j;

	for (j = 0; j < hdev->num_vmdq_vport + 1; j++) {
		for (i = 0; i < HCLGE_RSS_IND_TBL_SIZE; i++)
			vport[j].rss_indirection_tbl[i] =
				i % vport[j].alloc_rss_size;
	}
}