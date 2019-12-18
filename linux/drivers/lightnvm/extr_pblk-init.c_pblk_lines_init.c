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
struct pblk_line_mgmt {int nr_lines; } ;
struct pblk_line {int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
struct pblk {struct pblk_line* luns; struct pblk_line* lines; struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct pblk_line* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pblk_line*) ; 
 int pblk_alloc_line_meta (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 void* pblk_get_chunk_meta (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_meta_free (struct pblk_line_mgmt*,struct pblk_line*) ; 
 int pblk_line_meta_init (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_mg_free (struct pblk*) ; 
 int pblk_line_mg_init (struct pblk*) ; 
 int pblk_luns_init (struct pblk*) ; 
 int pblk_set_provision (struct pblk*,int) ; 
 scalar_t__ pblk_setup_line_meta (struct pblk*,struct pblk_line*,void*,int) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static int pblk_lines_init(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line *line;
	void *chunk_meta;
	int nr_free_chks = 0;
	int i, ret;

	ret = pblk_line_meta_init(pblk);
	if (ret)
		return ret;

	ret = pblk_line_mg_init(pblk);
	if (ret)
		return ret;

	ret = pblk_luns_init(pblk);
	if (ret)
		goto fail_free_meta;

	chunk_meta = pblk_get_chunk_meta(pblk);
	if (IS_ERR(chunk_meta)) {
		ret = PTR_ERR(chunk_meta);
		goto fail_free_luns;
	}

	pblk->lines = kcalloc(l_mg->nr_lines, sizeof(struct pblk_line),
								GFP_KERNEL);
	if (!pblk->lines) {
		ret = -ENOMEM;
		goto fail_free_chunk_meta;
	}

	for (i = 0; i < l_mg->nr_lines; i++) {
		line = &pblk->lines[i];

		ret = pblk_alloc_line_meta(pblk, line);
		if (ret)
			goto fail_free_lines;

		nr_free_chks += pblk_setup_line_meta(pblk, line, chunk_meta, i);

		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
								line->state);
	}

	if (!nr_free_chks) {
		pblk_err(pblk, "too many bad blocks prevent for sane instance\n");
		ret = -EINTR;
		goto fail_free_lines;
	}

	ret = pblk_set_provision(pblk, nr_free_chks);
	if (ret)
		goto fail_free_lines;

	vfree(chunk_meta);
	return 0;

fail_free_lines:
	while (--i >= 0)
		pblk_line_meta_free(l_mg, &pblk->lines[i]);
	kfree(pblk->lines);
fail_free_chunk_meta:
	vfree(chunk_meta);
fail_free_luns:
	kfree(pblk->luns);
fail_free_meta:
	pblk_line_mg_free(pblk);

	return ret;
}