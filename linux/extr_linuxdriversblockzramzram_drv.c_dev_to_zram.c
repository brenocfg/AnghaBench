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
struct zram {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 TYPE_1__* dev_to_disk (struct device*) ; 

__attribute__((used)) static inline struct zram *dev_to_zram(struct device *dev)
{
	return (struct zram *)dev_to_disk(dev)->private_data;
}