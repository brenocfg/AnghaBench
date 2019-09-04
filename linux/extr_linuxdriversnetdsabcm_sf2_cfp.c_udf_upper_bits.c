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

/* Variables and functions */
 int GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 int UDFS_PER_SLICE ; 

__attribute__((used)) static inline u32 udf_upper_bits(unsigned int num_udf)
{
	return GENMASK(num_udf - 1, 0) >> (UDFS_PER_SLICE - 1);
}