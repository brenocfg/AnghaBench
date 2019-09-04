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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct jit_ctx {int idx; int* image; struct sparc64_jit_data* offset; scalar_t__ saw_tail_call; scalar_t__ saw_call; scalar_t__ saw_frame_pointer; scalar_t__ tmp_3_used; scalar_t__ tmp_2_used; scalar_t__ tmp_1_used; struct bpf_prog* prog; } ;
struct sparc64_jit_data {struct bpf_binary_header* header; int /*<<< orphan*/ * image; struct jit_ctx ctx; } ;
struct bpf_prog {int jited; int jited_len; TYPE_1__* aux; int /*<<< orphan*/  is_func; void* bpf_func; int /*<<< orphan*/  len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int pages; } ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_2__ {struct sparc64_jit_data* jit_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bpf_flush_icache (struct bpf_binary_header*,int /*<<< orphan*/ *) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (int /*<<< orphan*/ ,int,int,int*) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 scalar_t__ build_body (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_epilogue (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_prologue (struct jit_ctx*) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 struct sparc64_jit_data* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sparc64_jit_data*) ; 
 struct sparc64_jit_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct jit_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,char,char,char,float,char,char) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	struct bpf_prog *tmp, *orig_prog = prog;
	struct sparc64_jit_data *jit_data;
	struct bpf_binary_header *header;
	bool tmp_blinded = false;
	bool extra_pass = false;
	struct jit_ctx ctx;
	u32 image_size;
	u8 *image_ptr;
	int pass;

	if (!prog->jit_requested)
		return orig_prog;

	tmp = bpf_jit_blind_constants(prog);
	/* If blinding was requested and we failed during blinding,
	 * we must fall back to the interpreter.
	 */
	if (IS_ERR(tmp))
		return orig_prog;
	if (tmp != prog) {
		tmp_blinded = true;
		prog = tmp;
	}

	jit_data = prog->aux->jit_data;
	if (!jit_data) {
		jit_data = kzalloc(sizeof(*jit_data), GFP_KERNEL);
		if (!jit_data) {
			prog = orig_prog;
			goto out;
		}
		prog->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.offset) {
		ctx = jit_data->ctx;
		image_ptr = jit_data->image;
		header = jit_data->header;
		extra_pass = true;
		image_size = sizeof(u32) * ctx.idx;
		goto skip_init_ctx;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.prog = prog;

	ctx.offset = kcalloc(prog->len, sizeof(unsigned int), GFP_KERNEL);
	if (ctx.offset == NULL) {
		prog = orig_prog;
		goto out_off;
	}

	/* Fake pass to detect features used, and get an accurate assessment
	 * of what the final image size will be.
	 */
	if (build_body(&ctx)) {
		prog = orig_prog;
		goto out_off;
	}
	build_prologue(&ctx);
	build_epilogue(&ctx);

	/* Now we know the actual image size. */
	image_size = sizeof(u32) * ctx.idx;
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      sizeof(u32), jit_fill_hole);
	if (header == NULL) {
		prog = orig_prog;
		goto out_off;
	}

	ctx.image = (u32 *)image_ptr;
skip_init_ctx:
	for (pass = 1; pass < 3; pass++) {
		ctx.idx = 0;

		build_prologue(&ctx);

		if (build_body(&ctx)) {
			bpf_jit_binary_free(header);
			prog = orig_prog;
			goto out_off;
		}

		build_epilogue(&ctx);

		if (bpf_jit_enable > 1)
			pr_info("Pass %d: shrink = %d, seen = [%c%c%c%c%c%c]\n", pass,
				image_size - (ctx.idx * 4),
				ctx.tmp_1_used ? '1' : ' ',
				ctx.tmp_2_used ? '2' : ' ',
				ctx.tmp_3_used ? '3' : ' ',
				ctx.saw_frame_pointer ? 'F' : ' ',
				ctx.saw_call ? 'C' : ' ',
				ctx.saw_tail_call ? 'T' : ' ');
	}

	if (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, image_size, pass, ctx.image);

	bpf_flush_icache(header, (u8 *)header + (header->pages * PAGE_SIZE));

	if (!prog->is_func || extra_pass) {
		bpf_jit_binary_lock_ro(header);
	} else {
		jit_data->ctx = ctx;
		jit_data->image = image_ptr;
		jit_data->header = header;
	}

	prog->bpf_func = (void *)ctx.image;
	prog->jited = 1;
	prog->jited_len = image_size;

	if (!prog->is_func || extra_pass) {
out_off:
		kfree(ctx.offset);
		kfree(jit_data);
		prog->aux->jit_data = NULL;
	}
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	return prog;
}