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
struct media_entity {int dummy; } ;

/* Variables and functions */
 scalar_t__ isp_pipeline_is_last (struct media_entity*) ; 
 int /*<<< orphan*/  isp_pipeline_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_isp_pipeline (struct media_entity*) ; 

__attribute__((used)) static void isp_suspend_module_pipeline(struct media_entity *me)
{
	if (isp_pipeline_is_last(me))
		isp_pipeline_suspend(to_isp_pipeline(me));
}