#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  adapter_type; } ;
struct TYPE_4__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;

/* Variables and functions */
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mr_exceeds_hw_limits(struct c4iw_dev *dev, u64 length)
{
	return (is_t4(dev->rdev.lldi.adapter_type) ||
		is_t5(dev->rdev.lldi.adapter_type)) &&
		length >= 8*1024*1024*1024ULL;
}