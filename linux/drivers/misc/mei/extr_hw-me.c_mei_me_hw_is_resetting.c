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
typedef  int u32 ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int ME_RST_HRA ; 
 int mei_me_mecsr_read (struct mei_device*) ; 

__attribute__((used)) static bool mei_me_hw_is_resetting(struct mei_device *dev)
{
	u32 mecsr = mei_me_mecsr_read(dev);

	return (mecsr & ME_RST_HRA) == ME_RST_HRA;
}