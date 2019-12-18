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
typedef  int /*<<< orphan*/  u64 ;
struct iavf_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iavf_add_one_ethtool_stat (int /*<<< orphan*/ ,void*,struct iavf_stats const*) ; 

__attribute__((used)) static void
__iavf_add_ethtool_stats(u64 **data, void *pointer,
			 const struct iavf_stats stats[],
			 const unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		iavf_add_one_ethtool_stat((*data)++, pointer, &stats[i]);
}