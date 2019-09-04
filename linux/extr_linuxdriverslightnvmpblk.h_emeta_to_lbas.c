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
struct TYPE_2__ {int* emeta_len; } ;
struct pblk {TYPE_1__ lm; } ;
struct line_emeta {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void *emeta_to_lbas(struct pblk *pblk, struct line_emeta *emeta)
{
	return ((void *)emeta + pblk->lm.emeta_len[1]);
}