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
struct r5l_log {struct r5l_io_unit* current_io; } ;
struct r5l_io_unit {int need_split_bio; int /*<<< orphan*/  current_bio; int /*<<< orphan*/  split_bio; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bio_add_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5_reserve_log_entry (struct r5l_log*,struct r5l_io_unit*) ; 
 int /*<<< orphan*/  r5l_bio_alloc (struct r5l_log*) ; 

__attribute__((used)) static void r5l_append_payload_page(struct r5l_log *log, struct page *page)
{
	struct r5l_io_unit *io = log->current_io;

	if (io->need_split_bio) {
		BUG_ON(io->split_bio);
		io->split_bio = io->current_bio;
		io->current_bio = r5l_bio_alloc(log);
		bio_chain(io->current_bio, io->split_bio);
		io->need_split_bio = false;
	}

	if (!bio_add_page(io->current_bio, page, PAGE_SIZE, 0))
		BUG();

	r5_reserve_log_entry(log, io);
}