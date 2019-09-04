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
struct r5conf {unsigned int retry_read_offset; struct bio* retry_read_aligned_list; struct bio* retry_read_aligned; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */

__attribute__((used)) static struct bio *remove_bio_from_retry(struct r5conf *conf,
					 unsigned int *offset)
{
	struct bio *bi;

	bi = conf->retry_read_aligned;
	if (bi) {
		*offset = conf->retry_read_offset;
		conf->retry_read_aligned = NULL;
		return bi;
	}
	bi = conf->retry_read_aligned_list;
	if(bi) {
		conf->retry_read_aligned_list = bi->bi_next;
		bi->bi_next = NULL;
		*offset = 0;
	}

	return bi;
}