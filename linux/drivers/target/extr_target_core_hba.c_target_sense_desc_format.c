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
struct se_device {TYPE_1__* transport; } ;
struct TYPE_2__ {scalar_t__ (* get_blocks ) (struct se_device*) ;} ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 scalar_t__ stub1 (struct se_device*) ; 

bool target_sense_desc_format(struct se_device *dev)
{
	return (dev) ? dev->transport->get_blocks(dev) > U32_MAX : false;
}