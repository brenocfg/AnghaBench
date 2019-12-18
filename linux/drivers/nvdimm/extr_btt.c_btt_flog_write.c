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
typedef  size_t u32 ;
struct log_entry {int /*<<< orphan*/  old_map; } ;
struct arena_info {TYPE_1__* freelist; } ;
struct TYPE_2__ {int seq; int has_err; int /*<<< orphan*/  block; scalar_t__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVDIMM_IO_ATOMIC ; 
 int __btt_log_write (struct arena_info*,size_t,size_t,struct log_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ ent_e_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ent_lba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btt_flog_write(struct arena_info *arena, u32 lane, u32 sub,
			struct log_entry *ent)
{
	int ret;

	ret = __btt_log_write(arena, lane, sub, ent, NVDIMM_IO_ATOMIC);
	if (ret)
		return ret;

	/* prepare the next free entry */
	arena->freelist[lane].sub = 1 - arena->freelist[lane].sub;
	if (++(arena->freelist[lane].seq) == 4)
		arena->freelist[lane].seq = 1;
	if (ent_e_flag(le32_to_cpu(ent->old_map)))
		arena->freelist[lane].has_err = 1;
	arena->freelist[lane].block = ent_lba(le32_to_cpu(ent->old_map));

	return ret;
}