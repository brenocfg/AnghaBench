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
struct r10conf {int /*<<< orphan*/  r10buf_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 

__attribute__((used)) static void close_sync(struct r10conf *conf)
{
	wait_barrier(conf);
	allow_barrier(conf);

	mempool_exit(&conf->r10buf_pool);
}