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
struct TYPE_2__ {scalar_t__ ahb_addr; } ;

/* Variables and functions */
 TYPE_1__* onenand ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline int s3c_read_cmd(unsigned int cmd)
{
	return readl(onenand->ahb_addr + cmd);
}