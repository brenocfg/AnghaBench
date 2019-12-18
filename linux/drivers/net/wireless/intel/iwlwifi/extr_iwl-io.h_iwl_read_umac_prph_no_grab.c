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
typedef  scalar_t__ u32 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ umac_prph_offset; } ;

/* Variables and functions */
 scalar_t__ iwl_read_prph_no_grab (struct iwl_trans*,scalar_t__) ; 

__attribute__((used)) static inline u32 iwl_read_umac_prph_no_grab(struct iwl_trans *trans, u32 ofs)
{
	return iwl_read_prph_no_grab(trans, ofs +
				     trans->trans_cfg->umac_prph_offset);
}