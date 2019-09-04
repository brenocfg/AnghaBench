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
struct ib_sge {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int ALIGN (size_t,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int U32_MAX ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *alloc_wr(size_t wr_size, __u32 num_sge)
{
	if (num_sge >= (U32_MAX - ALIGN(wr_size, sizeof (struct ib_sge))) /
		       sizeof (struct ib_sge))
		return NULL;

	return kmalloc(ALIGN(wr_size, sizeof (struct ib_sge)) +
			 num_sge * sizeof (struct ib_sge), GFP_KERNEL);
}