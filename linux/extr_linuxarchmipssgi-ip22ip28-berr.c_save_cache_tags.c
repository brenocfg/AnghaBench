#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long err_addr; TYPE_3__** tagi; TYPE_2__** tagd; TYPE_1__** tags; } ;
struct TYPE_7__ {void* hi; void* lo; } ;
struct TYPE_6__ {void* hi; void* lo; } ;
struct TYPE_5__ {void* hi; void* lo; } ;

/* Variables and functions */
 unsigned int CAC_BASE ; 
 int /*<<< orphan*/  Index_Load_Tag_D ; 
 int /*<<< orphan*/  Index_Load_Tag_I ; 
 int /*<<< orphan*/  Index_Load_Tag_S ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_4__ cache_tags ; 
 void* read_c0_taghi () ; 
 void* read_c0_taglo () ; 

__attribute__((used)) static inline void save_cache_tags(unsigned busaddr)
{
	unsigned long addr = CAC_BASE | busaddr;
	int i;
	cache_tags.err_addr = addr;

	/*
	 * Starting with a bus-address, save secondary cache (indexed by
	 * PA[23..18:7..6]) tags first.
	 */
	addr &= ~1L;
#define tag cache_tags.tags[0]
	cache_op(Index_Load_Tag_S, addr);
	tag[0].lo = read_c0_taglo();	/* PA[35:18], VA[13:12] */
	tag[0].hi = read_c0_taghi();	/* PA[39:36] */
	cache_op(Index_Load_Tag_S, addr | 1L);
	tag[1].lo = read_c0_taglo();	/* PA[35:18], VA[13:12] */
	tag[1].hi = read_c0_taghi();	/* PA[39:36] */
#undef tag

	/*
	 * Save all primary data cache (indexed by VA[13:5]) tags which
	 * might fit to this bus-address, knowing that VA[11:0] == PA[11:0].
	 * Saving all tags and evaluating them later is easier and safer
	 * than relying on VA[13:12] from the secondary cache tags to pick
	 * matching primary tags here already.
	 */
	addr &= (0xffL << 56) | ((1 << 12) - 1);
#define tag cache_tags.tagd[i]
	for (i = 0; i < 4; ++i, addr += (1 << 12)) {
		cache_op(Index_Load_Tag_D, addr);
		tag[0].lo = read_c0_taglo();	/* PA[35:12] */
		tag[0].hi = read_c0_taghi();	/* PA[39:36] */
		cache_op(Index_Load_Tag_D, addr | 1L);
		tag[1].lo = read_c0_taglo();	/* PA[35:12] */
		tag[1].hi = read_c0_taghi();	/* PA[39:36] */
	}
#undef tag

	/*
	 * Save primary instruction cache (indexed by VA[13:6]) tags
	 * the same way.
	 */
	addr &= (0xffL << 56) | ((1 << 12) - 1);
#define tag cache_tags.tagi[i]
	for (i = 0; i < 4; ++i, addr += (1 << 12)) {
		cache_op(Index_Load_Tag_I, addr);
		tag[0].lo = read_c0_taglo();	/* PA[35:12] */
		tag[0].hi = read_c0_taghi();	/* PA[39:36] */
		cache_op(Index_Load_Tag_I, addr | 1L);
		tag[1].lo = read_c0_taglo();	/* PA[35:12] */
		tag[1].hi = read_c0_taghi();	/* PA[39:36] */
	}
#undef tag
}