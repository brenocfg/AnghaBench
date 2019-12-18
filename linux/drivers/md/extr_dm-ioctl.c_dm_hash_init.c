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

/* Variables and functions */
 int /*<<< orphan*/  _name_buckets ; 
 int /*<<< orphan*/  _uuid_buckets ; 
 int /*<<< orphan*/  init_buckets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_hash_init(void)
{
	init_buckets(_name_buckets);
	init_buckets(_uuid_buckets);
	return 0;
}