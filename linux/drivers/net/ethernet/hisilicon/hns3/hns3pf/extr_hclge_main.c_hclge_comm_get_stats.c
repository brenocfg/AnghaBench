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
typedef  int u32 ;
struct hclge_comm_stats_str {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATS_READ (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *hclge_comm_get_stats(const void *comm_stats,
				 const struct hclge_comm_stats_str strs[],
				 int size, u64 *data)
{
	u64 *buf = data;
	u32 i;

	for (i = 0; i < size; i++)
		buf[i] = HCLGE_STATS_READ(comm_stats, strs[i].offset);

	return buf + size;
}