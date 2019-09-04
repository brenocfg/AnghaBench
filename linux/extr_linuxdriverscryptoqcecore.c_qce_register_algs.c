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
struct qce_algo_ops {int (* register_algs ) (struct qce_device*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct qce_algo_ops**) ; 
 int ENODEV ; 
 struct qce_algo_ops** qce_ops ; 
 int stub1 (struct qce_device*) ; 

__attribute__((used)) static int qce_register_algs(struct qce_device *qce)
{
	const struct qce_algo_ops *ops;
	int i, ret = -ENODEV;

	for (i = 0; i < ARRAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		ret = ops->register_algs(qce);
		if (ret)
			break;
	}

	return ret;
}