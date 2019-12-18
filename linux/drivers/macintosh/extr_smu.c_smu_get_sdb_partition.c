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
struct smu_sdbp_header {int dummy; } ;

/* Variables and functions */
 struct smu_sdbp_header const* __smu_get_sdb_partition (int,unsigned int*,int /*<<< orphan*/ ) ; 

const struct smu_sdbp_header *smu_get_sdb_partition(int id, unsigned int *size)
{
	return __smu_get_sdb_partition(id, size, 0);
}