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
typedef  scalar_t__ u32 ;
struct pblk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  identifier; } ;
struct line_emeta {TYPE_1__ header; int /*<<< orphan*/  crc; } ;

/* Variables and functions */
 scalar_t__ PBLK_MAGIC ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_calc_emeta_crc (struct pblk*,struct line_emeta*) ; 

int pblk_recov_check_emeta(struct pblk *pblk, struct line_emeta *emeta_buf)
{
	u32 crc;

	crc = pblk_calc_emeta_crc(pblk, emeta_buf);
	if (le32_to_cpu(emeta_buf->crc) != crc)
		return 1;

	if (le32_to_cpu(emeta_buf->header.identifier) != PBLK_MAGIC)
		return 1;

	return 0;
}