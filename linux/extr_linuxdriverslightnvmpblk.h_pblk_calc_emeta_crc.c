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
struct pblk_line_meta {int* emeta_len; } ;
struct pblk {struct pblk_line_meta lm; } ;
struct line_header {int dummy; } ;
struct line_emeta {int dummy; } ;
typedef  int /*<<< orphan*/  crc ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static inline u32 pblk_calc_emeta_crc(struct pblk *pblk,
				      struct line_emeta *emeta)
{
	struct pblk_line_meta *lm = &pblk->lm;
	u32 crc = ~(u32)0;

	crc = crc32_le(crc, (unsigned char *)emeta +
				sizeof(struct line_header) + sizeof(crc),
				lm->emeta_len[0] -
				sizeof(struct line_header) - sizeof(crc));

	return crc;
}