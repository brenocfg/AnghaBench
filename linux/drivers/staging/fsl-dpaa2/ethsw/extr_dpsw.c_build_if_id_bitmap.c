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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int const) ; 
 int DPSW_MAX_IF ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_if_id_bitmap(__le64 *bmap,
			       const u16 *id,
			       const u16 num_ifs)
{
	int i;

	for (i = 0; (i < num_ifs) && (i < DPSW_MAX_IF); i++) {
		if (id[i] < DPSW_MAX_IF)
			bmap[id[i] / 64] |= cpu_to_le64(BIT_MASK(id[i] % 64));
	}
}