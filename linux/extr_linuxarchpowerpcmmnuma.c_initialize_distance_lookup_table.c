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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** distance_lookup_table ; 
 int /*<<< orphan*/ * distance_ref_points ; 
 int distance_ref_points_depth ; 
 int /*<<< orphan*/  form1_affinity ; 
 int /*<<< orphan*/  of_read_number (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void initialize_distance_lookup_table(int nid,
		const __be32 *associativity)
{
	int i;

	if (!form1_affinity)
		return;

	for (i = 0; i < distance_ref_points_depth; i++) {
		const __be32 *entry;

		entry = &associativity[be32_to_cpu(distance_ref_points[i]) - 1];
		distance_lookup_table[nid][i] = of_read_number(entry, 1);
	}
}