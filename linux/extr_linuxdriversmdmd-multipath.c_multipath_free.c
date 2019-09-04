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
struct mpconf {struct mpconf* multipaths; int /*<<< orphan*/  pool; } ;
struct mddev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mpconf*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multipath_free(struct mddev *mddev, void *priv)
{
	struct mpconf *conf = priv;

	mempool_exit(&conf->pool);
	kfree(conf->multipaths);
	kfree(conf);
}