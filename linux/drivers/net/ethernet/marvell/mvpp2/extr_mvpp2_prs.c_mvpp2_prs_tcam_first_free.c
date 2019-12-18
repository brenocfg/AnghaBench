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
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char MVPP2_PRS_TCAM_SRAM_SIZE ; 
 int /*<<< orphan*/  swap (unsigned char,unsigned char) ; 

__attribute__((used)) static int mvpp2_prs_tcam_first_free(struct mvpp2 *priv, unsigned char start,
				     unsigned char end)
{
	int tid;

	if (start > end)
		swap(start, end);

	if (end >= MVPP2_PRS_TCAM_SRAM_SIZE)
		end = MVPP2_PRS_TCAM_SRAM_SIZE - 1;

	for (tid = start; tid <= end; tid++) {
		if (!priv->prs_shadow[tid].valid)
			return tid;
	}

	return -EINVAL;
}