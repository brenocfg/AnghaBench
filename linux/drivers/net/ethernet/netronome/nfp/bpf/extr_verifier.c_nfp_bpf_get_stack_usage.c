#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_prog {TYPE_1__* subprog; } ;
struct TYPE_4__ {scalar_t__ imm; } ;
struct nfp_insn_meta {unsigned short subprog_idx; TYPE_2__ insn; scalar_t__ n; } ;
struct TYPE_3__ {unsigned short stack_depth; } ;

/* Variables and functions */
 int MAX_CALL_FRAMES ; 
 int /*<<< orphan*/  STACK_FRAME_ALIGN ; 
 int /*<<< orphan*/  is_mbpf_pseudo_call (struct nfp_insn_meta*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 struct nfp_insn_meta* nfp_bpf_goto_meta (struct nfp_prog*,struct nfp_insn_meta*,scalar_t__) ; 
 struct nfp_insn_meta* nfp_meta_next (struct nfp_insn_meta*) ; 
 struct nfp_insn_meta* nfp_prog_first_meta (struct nfp_prog*) ; 
 struct nfp_insn_meta* nfp_prog_last_meta (struct nfp_prog*) ; 
 unsigned short round_up (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nfp_bpf_get_stack_usage(struct nfp_prog *nfp_prog)
{
	struct nfp_insn_meta *meta = nfp_prog_first_meta(nfp_prog);
	unsigned int max_depth = 0, depth = 0, frame = 0;
	struct nfp_insn_meta *ret_insn[MAX_CALL_FRAMES];
	unsigned short frame_depths[MAX_CALL_FRAMES];
	unsigned short ret_prog[MAX_CALL_FRAMES];
	unsigned short idx = meta->subprog_idx;

	/* Inspired from check_max_stack_depth() from kernel verifier.
	 * Starting from main subprogram, walk all instructions and recursively
	 * walk all callees that given subprogram can call. Since recursion is
	 * prevented by the kernel verifier, this algorithm only needs a local
	 * stack of MAX_CALL_FRAMES to remember callsites.
	 */
process_subprog:
	frame_depths[frame] = nfp_prog->subprog[idx].stack_depth;
	frame_depths[frame] = round_up(frame_depths[frame], STACK_FRAME_ALIGN);
	depth += frame_depths[frame];
	max_depth = max(max_depth, depth);

continue_subprog:
	for (; meta != nfp_prog_last_meta(nfp_prog) && meta->subprog_idx == idx;
	     meta = nfp_meta_next(meta)) {
		if (!is_mbpf_pseudo_call(meta))
			continue;

		/* We found a call to a subprogram. Remember instruction to
		 * return to and subprog id.
		 */
		ret_insn[frame] = nfp_meta_next(meta);
		ret_prog[frame] = idx;

		/* Find the callee and start processing it. */
		meta = nfp_bpf_goto_meta(nfp_prog, meta,
					 meta->n + 1 + meta->insn.imm);
		idx = meta->subprog_idx;
		frame++;
		goto process_subprog;
	}
	/* End of for() loop means the last instruction of the subprog was
	 * reached. If we popped all stack frames, return; otherwise, go on
	 * processing remaining instructions from the caller.
	 */
	if (frame == 0)
		return max_depth;

	depth -= frame_depths[frame];
	frame--;
	meta = ret_insn[frame];
	idx = ret_prog[frame];
	goto continue_subprog;
}