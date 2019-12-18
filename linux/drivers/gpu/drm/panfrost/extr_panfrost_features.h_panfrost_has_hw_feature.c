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
struct TYPE_2__ {int /*<<< orphan*/  hw_features; } ;
struct panfrost_device {TYPE_1__ features; } ;
typedef  enum panfrost_hw_feature { ____Placeholder_panfrost_hw_feature } panfrost_hw_feature ;

/* Variables and functions */
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool panfrost_has_hw_feature(struct panfrost_device *pfdev,
					   enum panfrost_hw_feature feat)
{
	return test_bit(feat, pfdev->features.hw_features);
}