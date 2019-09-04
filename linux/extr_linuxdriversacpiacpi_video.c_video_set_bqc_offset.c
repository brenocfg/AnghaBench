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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int bqc_offset_aml_bug_workaround ; 

__attribute__((used)) static int video_set_bqc_offset(const struct dmi_system_id *d)
{
	bqc_offset_aml_bug_workaround = 9;
	return 0;
}