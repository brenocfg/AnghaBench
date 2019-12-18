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
struct cache_set {int dummy; } ;

/* Variables and functions */
 int __uuid_write (struct cache_set*) ; 
 int /*<<< orphan*/  bch_journal_meta (struct cache_set*,int /*<<< orphan*/ *) ; 

int bch_uuid_write(struct cache_set *c)
{
	int ret = __uuid_write(c);

	if (!ret)
		bch_journal_meta(c, NULL);

	return ret;
}