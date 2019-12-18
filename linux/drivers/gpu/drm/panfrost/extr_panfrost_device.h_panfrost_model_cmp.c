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
struct TYPE_2__ {int id; } ;
struct panfrost_device {TYPE_1__ features; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static inline int panfrost_model_cmp(struct panfrost_device *pfdev, s32 id)
{
	s32 match_id = pfdev->features.id;

	if (match_id & 0xf000)
		match_id &= 0xf00f;
	return match_id - id;
}