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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_rm_hw_iter {int type; int /*<<< orphan*/  enc_id; } ;
typedef  enum dpu_hw_blk_type { ____Placeholder_dpu_hw_blk_type } dpu_hw_blk_type ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int) ; 

void dpu_rm_init_hw_iter(
		struct dpu_rm_hw_iter *iter,
		uint32_t enc_id,
		enum dpu_hw_blk_type type)
{
	memset(iter, 0, sizeof(*iter));
	iter->enc_id = enc_id;
	iter->type = type;
}