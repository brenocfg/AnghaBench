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
struct bpf_prog {int jited; scalar_t__ jited_len; void* bpf_func; scalar_t__ len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_jit {scalar_t__ size; int /*<<< orphan*/ * addrs; scalar_t__ prg_buf; int /*<<< orphan*/  size_prg; } ;
struct bpf_binary_header {int dummy; } ;
typedef  int /*<<< orphan*/  jit ;

/* Variables and functions */
 scalar_t__ BPF_SIZE_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (scalar_t__,scalar_t__,int,scalar_t__) ; 
 int bpf_jit_enable ; 
 scalar_t__ bpf_jit_prog (struct bpf_jit*,struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 int /*<<< orphan*/ * kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct bpf_jit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_fn_code (scalar_t__,int /*<<< orphan*/ ) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *fp)
{
	struct bpf_prog *tmp, *orig_fp = fp;
	struct bpf_binary_header *header;
	bool tmp_blinded = false;
	struct bpf_jit jit;
	int pass;

	if (!fp->jit_requested)
		return orig_fp;

	tmp = bpf_jit_blind_constants(fp);
	/*
	 * If blinding was requested and we failed during blinding,
	 * we must fall back to the interpreter.
	 */
	if (IS_ERR(tmp))
		return orig_fp;
	if (tmp != fp) {
		tmp_blinded = true;
		fp = tmp;
	}

	memset(&jit, 0, sizeof(jit));
	jit.addrs = kcalloc(fp->len + 1, sizeof(*jit.addrs), GFP_KERNEL);
	if (jit.addrs == NULL) {
		fp = orig_fp;
		goto out;
	}
	/*
	 * Three initial passes:
	 *   - 1/2: Determine clobbered registers
	 *   - 3:   Calculate program size and addrs arrray
	 */
	for (pass = 1; pass <= 3; pass++) {
		if (bpf_jit_prog(&jit, fp)) {
			fp = orig_fp;
			goto free_addrs;
		}
	}
	/*
	 * Final pass: Allocate and generate program
	 */
	if (jit.size >= BPF_SIZE_MAX) {
		fp = orig_fp;
		goto free_addrs;
	}
	header = bpf_jit_binary_alloc(jit.size, &jit.prg_buf, 2, jit_fill_hole);
	if (!header) {
		fp = orig_fp;
		goto free_addrs;
	}
	if (bpf_jit_prog(&jit, fp)) {
		bpf_jit_binary_free(header);
		fp = orig_fp;
		goto free_addrs;
	}
	if (bpf_jit_enable > 1) {
		bpf_jit_dump(fp->len, jit.size, pass, jit.prg_buf);
		print_fn_code(jit.prg_buf, jit.size_prg);
	}
	bpf_jit_binary_lock_ro(header);
	fp->bpf_func = (void *) jit.prg_buf;
	fp->jited = 1;
	fp->jited_len = jit.size;
free_addrs:
	kfree(jit.addrs);
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(fp, fp == orig_fp ?
					   tmp : orig_fp);
	return fp;
}