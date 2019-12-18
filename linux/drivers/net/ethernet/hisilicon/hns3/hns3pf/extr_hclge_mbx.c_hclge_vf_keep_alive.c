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
struct hclge_vport {int /*<<< orphan*/  last_active_jiffies; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void hclge_vf_keep_alive(struct hclge_vport *vport,
				struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	vport->last_active_jiffies = jiffies;
}