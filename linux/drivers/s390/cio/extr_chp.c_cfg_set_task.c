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
struct chp_id {size_t cssid; size_t id; } ;
typedef  enum cfg_task_t { ____Placeholder_cfg_task_t } cfg_task_t ;

/* Variables and functions */
 int** chp_cfg_task ; 

__attribute__((used)) static void cfg_set_task(struct chp_id chpid, enum cfg_task_t cfg)
{
	chp_cfg_task[chpid.cssid][chpid.id] = cfg;
}