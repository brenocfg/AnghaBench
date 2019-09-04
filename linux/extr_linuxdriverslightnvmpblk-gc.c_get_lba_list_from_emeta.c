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
struct pblk_line_mgmt {int /*<<< orphan*/  emeta_alloc_type; } ;
struct pblk_line_meta {unsigned int* emeta_len; } ;
struct pblk_line {int /*<<< orphan*/  id; } ;
struct pblk {struct pblk_line_meta lm; struct pblk_line_mgmt l_mg; } ;
struct line_emeta {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  emeta_to_lbas (struct pblk*,struct line_emeta*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,...) ; 
 int pblk_line_read_emeta (struct pblk*,struct pblk_line*,struct line_emeta*) ; 
 void* pblk_malloc (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_mfree (struct line_emeta*,int /*<<< orphan*/ ) ; 
 int pblk_recov_check_emeta (struct pblk*,struct line_emeta*) ; 

__attribute__((used)) static __le64 *get_lba_list_from_emeta(struct pblk *pblk,
				       struct pblk_line *line)
{
	struct line_emeta *emeta_buf;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line_meta *lm = &pblk->lm;
	unsigned int lba_list_size = lm->emeta_len[2];
	__le64 *lba_list;
	int ret;

	emeta_buf = pblk_malloc(lm->emeta_len[0],
				l_mg->emeta_alloc_type, GFP_KERNEL);
	if (!emeta_buf)
		return NULL;

	ret = pblk_line_read_emeta(pblk, line, emeta_buf);
	if (ret) {
		pblk_err(pblk, "line %d read emeta failed (%d)\n",
				line->id, ret);
		pblk_mfree(emeta_buf, l_mg->emeta_alloc_type);
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
		pblk_mfree(emeta_buf, l_mg->emeta_alloc_type);
		return NULL;
	}

	lba_list = pblk_malloc(lba_list_size,
			       l_mg->emeta_alloc_type, GFP_KERNEL);
	if (lba_list)
		memcpy(lba_list, emeta_to_lbas(pblk, emeta_buf), lba_list_size);

	pblk_mfree(emeta_buf, l_mg->emeta_alloc_type);

	return lba_list;
}