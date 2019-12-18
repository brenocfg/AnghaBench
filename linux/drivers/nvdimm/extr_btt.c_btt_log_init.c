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
typedef  scalar_t__ u32 ;
struct log_entry {void* seq; void* new_map; void* old_map; void* lba; } ;
struct arena_info {size_t info2off; size_t logoff; scalar_t__ nfree; scalar_t__ external_nlba; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (size_t,int) ; 
 scalar_t__ LOG_SEQ_INIT ; 
 size_t SZ_4K ; 
 int __btt_log_write (struct arena_info*,scalar_t__,int /*<<< orphan*/ ,struct log_entry*,int /*<<< orphan*/ ) ; 
 int arena_write_bytes (struct arena_info*,size_t,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  to_dev (struct arena_info*) ; 

__attribute__((used)) static int btt_log_init(struct arena_info *arena)
{
	size_t logsize = arena->info2off - arena->logoff;
	size_t chunk_size = SZ_4K, offset = 0;
	struct log_entry ent;
	void *zerobuf;
	int ret;
	u32 i;

	zerobuf = kzalloc(chunk_size, GFP_KERNEL);
	if (!zerobuf)
		return -ENOMEM;
	/*
	 * logoff should always be at least 512B  aligned. We rely on that to
	 * make sure rw_bytes does error clearing correctly, so make sure that
	 * is the case.
	 */
	dev_WARN_ONCE(to_dev(arena), !IS_ALIGNED(arena->logoff, 512),
		"arena->logoff: %#llx is unaligned\n", arena->logoff);

	while (logsize) {
		size_t size = min(logsize, chunk_size);

		dev_WARN_ONCE(to_dev(arena), size < 512,
			"chunk size: %#zx is unaligned\n", size);
		ret = arena_write_bytes(arena, arena->logoff + offset, zerobuf,
				size, 0);
		if (ret)
			goto free;

		offset += size;
		logsize -= size;
		cond_resched();
	}

	for (i = 0; i < arena->nfree; i++) {
		ent.lba = cpu_to_le32(i);
		ent.old_map = cpu_to_le32(arena->external_nlba + i);
		ent.new_map = cpu_to_le32(arena->external_nlba + i);
		ent.seq = cpu_to_le32(LOG_SEQ_INIT);
		ret = __btt_log_write(arena, i, 0, &ent, 0);
		if (ret)
			goto free;
	}

 free:
	kfree(zerobuf);
	return ret;
}