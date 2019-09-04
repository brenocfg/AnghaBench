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
struct qce_device {int dummy; } ;
struct qce_algo_ops {int /*<<< orphan*/  (* unregister_algs ) (struct qce_device*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct qce_algo_ops**) ; 
 struct qce_algo_ops** qce_ops ; 
 int /*<<< orphan*/  stub1 (struct qce_device*) ; 

__attribute__((used)) static void qce_unregister_algs(struct qce_device *qce)
{
	const struct qce_algo_ops *ops;
	int i;

	for (i = 0; i < ARRAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		ops->unregister_algs(qce);
	}
}