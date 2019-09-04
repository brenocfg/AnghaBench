#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct mic_device {TYPE_1__* intr_info; } ;
typedef  enum mic_intr_type { ____Placeholder_mic_intr_type } mic_intr_type ;
struct TYPE_2__ {int* intr_len; scalar_t__* intr_start_idx; } ;

/* Variables and functions */
 int MIC_NUM_INTR_TYPES ; 
 scalar_t__ MIC_NUM_OFFSETS ; 

__attribute__((used)) static u16 mic_map_src_to_offset(struct mic_device *mdev,
				 int intr_src, enum mic_intr_type type)
{
	if (type >= MIC_NUM_INTR_TYPES)
		return MIC_NUM_OFFSETS;
	if (intr_src >= mdev->intr_info->intr_len[type])
		return MIC_NUM_OFFSETS;

	return mdev->intr_info->intr_start_idx[type] + intr_src;
}