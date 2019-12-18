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
typedef  void* u64 ;
struct wa_counters {int /*<<< orphan*/  gc; int /*<<< orphan*/  pad; int /*<<< orphan*/  user; } ;
struct pblk_line_meta {int dummy; } ;
struct pblk {void* gc_rst_wa; void* pad_rst_wa; void* user_rst_wa; int /*<<< orphan*/  gc_wa; int /*<<< orphan*/  pad_wa; int /*<<< orphan*/  user_wa; struct pblk_line_meta lm; } ;
struct line_header {scalar_t__ version_major; int version_minor; } ;
struct line_emeta {struct line_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,void*) ; 
 struct wa_counters* emeta_to_wa (struct pblk_line_meta*,struct line_emeta*) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_recov_wa_counters(struct pblk *pblk,
				   struct line_emeta *emeta)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct line_header *header = &emeta->header;
	struct wa_counters *wa = emeta_to_wa(lm, emeta);

	/* WA counters were introduced in emeta version 0.2 */
	if (header->version_major > 0 || header->version_minor >= 2) {
		u64 user = le64_to_cpu(wa->user);
		u64 pad = le64_to_cpu(wa->pad);
		u64 gc = le64_to_cpu(wa->gc);

		atomic64_set(&pblk->user_wa, user);
		atomic64_set(&pblk->pad_wa, pad);
		atomic64_set(&pblk->gc_wa, gc);

		pblk->user_rst_wa = user;
		pblk->pad_rst_wa = pad;
		pblk->gc_rst_wa = gc;
	}
}