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
struct smu_context {int dummy; } ;
typedef  enum smu_feature_mask { ____Placeholder_smu_feature_mask } smu_feature_mask ;

/* Variables and functions */
 int SMU_FEATURE_COUNT ; 
 char const** __smu_feature_names ; 

const char *smu_get_feature_name(struct smu_context *smu, enum smu_feature_mask feature)
{
	if (feature < 0 || feature >= SMU_FEATURE_COUNT)
		return "unknown smu feature";
	return __smu_feature_names[feature];
}