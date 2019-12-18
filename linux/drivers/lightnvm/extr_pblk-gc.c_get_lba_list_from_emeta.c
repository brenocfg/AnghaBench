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
struct pblk_line_meta {unsigned int* emeta_len; } ;
struct pblk_line {int /*<<< orphan*/  id; } ;
struct pblk {struct pblk_line_meta lm; } ;
struct line_emeta {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  emeta_to_lbas (struct pblk*,struct line_emeta*) ; 
 int /*<<< orphan*/  kvfree (struct line_emeta*) ; 
 void* kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,...) ; 
 int pblk_line_emeta_read (struct pblk*,struct pblk_line*,struct line_emeta*) ; 
 int pblk_recov_check_emeta (struct pblk*,struct line_emeta*) ; 

__attribute__((used)) static __le64 *get_lba_list_from_emeta(struct pblk *pblk,
				       struct pblk_line *line)
{
	struct line_emeta *emeta_buf;
	struct pblk_line_meta *lm = &pblk->lm;
	unsigned int lba_list_size = lm->emeta_len[2];
	__le64 *lba_list;
	int ret;

	emeta_buf = kvmalloc(lm->emeta_len[0], GFP_KERNEL);
	if (!emeta_buf)
		return NULL;

	ret = pblk_line_emeta_read(pblk, line, emeta_buf);
	if (ret) {
		pblk_err(pblk, "line %d read emeta failed (%d)\n",
				line->id, ret);
		kvfree(emeta_buf);
		return NULL;
	}

	/* If this read fails, it means that emeta is corrupted.
	 * For now, leave the line untouched.
	 * TODO: Implement a recovery routine that scans and moves
	 * all sectors on the line.
	 */

	ret = pblk_recov_check_emeta(pblk, emeta_buf);
	if (ret) {
		pblk_err(pblk, "inconsistent emeta (line %d)\n",
				line->id);
		kvfree(emeta_buf);
		return NULL;
	}

	lba_list = kvmalloc(lba_list_size, GFP_KERNEL);

	if (lba_list)
		memcpy(lba_list, emeta_to_lbas(pblk, emeta_buf), lba_list_size);

	kvfree(emeta_buf);

	return lba_list;
}