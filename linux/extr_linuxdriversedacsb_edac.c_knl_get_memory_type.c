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
struct sbridge_pvt {int dummy; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;

/* Variables and functions */
 int MEM_RDDR4 ; 

__attribute__((used)) static enum mem_type knl_get_memory_type(struct sbridge_pvt *pvt)
{
	/* DDR4 RDIMMS and LRDIMMS are supported */
	return MEM_RDDR4;
}