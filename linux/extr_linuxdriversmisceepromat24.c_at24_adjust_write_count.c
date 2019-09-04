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
struct at24_data {size_t write_max; int /*<<< orphan*/  page_size; } ;

/* Variables and functions */
 unsigned int roundup (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t at24_adjust_write_count(struct at24_data *at24,
				      unsigned int offset, size_t count)
{
	unsigned int next_page;

	/* write_max is at most a page */
	if (count > at24->write_max)
		count = at24->write_max;

	/* Never roll over backwards, to the start of this page */
	next_page = roundup(offset + 1, at24->page_size);
	if (offset + count > next_page)
		count = next_page - offset;

	return count;
}