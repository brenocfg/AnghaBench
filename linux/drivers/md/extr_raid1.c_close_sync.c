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
struct r1conf {int /*<<< orphan*/  r1buf_pool; } ;

/* Variables and functions */
 int BARRIER_BUCKETS_NR ; 
 int /*<<< orphan*/  _allow_barrier (struct r1conf*,int) ; 
 int /*<<< orphan*/  _wait_barrier (struct r1conf*,int) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_sync(struct r1conf *conf)
{
	int idx;

	for (idx = 0; idx < BARRIER_BUCKETS_NR; idx++) {
		_wait_barrier(conf, idx);
		_allow_barrier(conf, idx);
	}

	mempool_exit(&conf->r1buf_pool);
}