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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_caam32 (int) ; 
 int desc_len (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline void set_jump_tgt_here(u32 * const desc, u32 *jump_cmd)
{
	*jump_cmd = cpu_to_caam32(caam32_to_cpu(*jump_cmd) |
				  (desc_len(desc) - (jump_cmd - desc)));
}