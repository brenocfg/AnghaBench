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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void restore_other_spu_access(struct spu_state *csa,
					    struct spu *spu)
{
	/* Restore, Step 70:
	 *     Restore other SPU mappings to this SPU. TBD.
	 */
}