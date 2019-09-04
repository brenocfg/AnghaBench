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
struct ena_com_dev {int /*<<< orphan*/  rss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_com_hash_ctrl_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_hash_key_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_indirect_table_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

void ena_com_rss_destroy(struct ena_com_dev *ena_dev)
{
	ena_com_indirect_table_destroy(ena_dev);
	ena_com_hash_key_destroy(ena_dev);
	ena_com_hash_ctrl_destroy(ena_dev);

	memset(&ena_dev->rss, 0x0, sizeof(ena_dev->rss));
}