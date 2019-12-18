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
struct stm32_dcmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcmi_pipeline_s_stream (struct stm32_dcmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dcmi_pipeline_stop(struct stm32_dcmi *dcmi)
{
	dcmi_pipeline_s_stream(dcmi, 0);
}