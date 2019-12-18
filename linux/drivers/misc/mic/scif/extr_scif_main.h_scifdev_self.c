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
struct scif_dev {scalar_t__ node; } ;
struct TYPE_2__ {scalar_t__ nodeid; } ;

/* Variables and functions */
 TYPE_1__ scif_info ; 

__attribute__((used)) static inline int scifdev_self(struct scif_dev *dev)
{
	return dev->node == scif_info.nodeid;
}