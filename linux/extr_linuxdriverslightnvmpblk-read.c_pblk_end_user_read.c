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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 

__attribute__((used)) static void pblk_end_user_read(struct bio *bio)
{
#ifdef CONFIG_NVM_PBLK_DEBUG
	WARN_ONCE(bio->bi_status, "pblk: corrupted read bio\n");
#endif
	bio_endio(bio);
}