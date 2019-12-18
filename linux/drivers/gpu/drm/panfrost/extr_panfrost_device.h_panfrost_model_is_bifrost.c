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
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ panfrost_model_cmp (struct panfrost_device*,int) ; 

__attribute__((used)) static inline bool panfrost_model_is_bifrost(struct panfrost_device *pfdev)
{
	return panfrost_model_cmp(pfdev, 0x1000) >= 0;
}