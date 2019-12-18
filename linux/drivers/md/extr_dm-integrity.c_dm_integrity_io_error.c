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
struct dm_integrity_c {int /*<<< orphan*/  failed; int /*<<< orphan*/  number_of_mismatches; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char const*,int) ; 
 int EILSEQ ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_integrity_io_error(struct dm_integrity_c *ic, const char *msg, int err)
{
	if (err == -EILSEQ)
		atomic64_inc(&ic->number_of_mismatches);
	if (!cmpxchg(&ic->failed, 0, err))
		DMERR("Error on %s: %d", msg, err);
}