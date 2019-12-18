#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct journal_write {TYPE_2__* c; } ;
struct bio {int /*<<< orphan*/  bi_status; struct journal_write* bi_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  io; } ;
struct TYPE_4__ {TYPE_1__ journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_set_err_on (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void journal_write_endio(struct bio *bio)
{
	struct journal_write *w = bio->bi_private;

	cache_set_err_on(bio->bi_status, w->c, "journal io error");
	closure_put(&w->c->journal.io);
}