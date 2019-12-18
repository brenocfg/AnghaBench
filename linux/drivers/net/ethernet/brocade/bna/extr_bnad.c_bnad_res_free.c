#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnad {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_info; } ;
struct bna_res_info {TYPE_1__ res_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnad_mem_free (struct bnad*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_res_free(struct bnad *bnad, struct bna_res_info *res_info,
		u32 res_val_max)
{
	int i;

	for (i = 0; i < res_val_max; i++)
		bnad_mem_free(bnad, &res_info[i].res_u.mem_info);
}