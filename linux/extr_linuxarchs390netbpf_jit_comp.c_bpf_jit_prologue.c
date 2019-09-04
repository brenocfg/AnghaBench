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
struct bpf_jit {int seen; int /*<<< orphan*/  prg; int /*<<< orphan*/  base_ip; int /*<<< orphan*/  tail_call_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_REG_FP ; 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT4 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT4_DISP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT4_IMM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT4_PCREL (int,int) ; 
 int /*<<< orphan*/  EMIT6_DISP_LH (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REGS_SAVE ; 
 int /*<<< orphan*/  REG_0 ; 
 int /*<<< orphan*/  REG_15 ; 
 int /*<<< orphan*/  REG_L ; 
 int /*<<< orphan*/  REG_W1 ; 
 int SEEN_FUNC ; 
 int SEEN_LITERAL ; 
 int SEEN_STACK ; 
 int SEEN_TAIL_CALL ; 
 int /*<<< orphan*/  STK_160_UNUSED ; 
 int /*<<< orphan*/  STK_OFF ; 
 int STK_OFF_TCCNT ; 
 int /*<<< orphan*/  _EMIT2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EMIT6 (int,int) ; 
 int /*<<< orphan*/  save_restore_regs (struct bpf_jit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_jit_prologue(struct bpf_jit *jit, u32 stack_depth)
{
	if (jit->seen & SEEN_TAIL_CALL) {
		/* xc STK_OFF_TCCNT(4,%r15),STK_OFF_TCCNT(%r15) */
		_EMIT6(0xd703f000 | STK_OFF_TCCNT, 0xf000 | STK_OFF_TCCNT);
	} else {
		/* j tail_call_start: NOP if no tail calls are used */
		EMIT4_PCREL(0xa7f40000, 6);
		_EMIT2(0);
	}
	/* Tail calls have to skip above initialization */
	jit->tail_call_start = jit->prg;
	/* Save registers */
	save_restore_regs(jit, REGS_SAVE, stack_depth);
	/* Setup literal pool */
	if (jit->seen & SEEN_LITERAL) {
		/* basr %r13,0 */
		EMIT2(0x0d00, REG_L, REG_0);
		jit->base_ip = jit->prg;
	}
	/* Setup stack and backchain */
	if (jit->seen & SEEN_STACK) {
		if (jit->seen & SEEN_FUNC)
			/* lgr %w1,%r15 (backchain) */
			EMIT4(0xb9040000, REG_W1, REG_15);
		/* la %bfp,STK_160_UNUSED(%r15) (BPF frame pointer) */
		EMIT4_DISP(0x41000000, BPF_REG_FP, REG_15, STK_160_UNUSED);
		/* aghi %r15,-STK_OFF */
		EMIT4_IMM(0xa70b0000, REG_15, -(STK_OFF + stack_depth));
		if (jit->seen & SEEN_FUNC)
			/* stg %w1,152(%r15) (backchain) */
			EMIT6_DISP_LH(0xe3000000, 0x0024, REG_W1, REG_0,
				      REG_15, 152);
	}
}