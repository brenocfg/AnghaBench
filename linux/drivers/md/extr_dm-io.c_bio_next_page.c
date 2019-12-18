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
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct dpages {TYPE_1__ context_bi; scalar_t__ context_ptr; } ;
struct bio_vec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bvec_iter_advance (struct bio_vec*,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void bio_next_page(struct dpages *dp)
{
	unsigned int len = (unsigned int)dp->context_bi.bi_sector;

	bvec_iter_advance((struct bio_vec *)dp->context_ptr,
			  &dp->context_bi, len);
}