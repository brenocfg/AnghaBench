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
struct hinic_dev {int /*<<< orphan*/  rss_tmpl_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_rss_cfg (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hinic_rss_deinit(struct hinic_dev *nic_dev)
{
	hinic_rss_cfg(nic_dev, 0, nic_dev->rss_tmpl_idx);
}