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
struct io_notify {int /*<<< orphan*/  c; int /*<<< orphan*/  count; int /*<<< orphan*/  wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writecache_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void writecache_notify_io(unsigned long error, void *context)
{
	struct io_notify *endio = context;

	if (unlikely(error != 0))
		writecache_error(endio->wc, -EIO, "error writing metadata");
	BUG_ON(atomic_read(&endio->count) <= 0);
	if (atomic_dec_and_test(&endio->count))
		complete(&endio->c);
}