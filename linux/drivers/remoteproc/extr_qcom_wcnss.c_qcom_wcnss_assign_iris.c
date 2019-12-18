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
struct qcom_wcnss {int use_48mhz_xo; int /*<<< orphan*/  iris_lock; struct qcom_iris* iris; } ;
struct qcom_iris {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void qcom_wcnss_assign_iris(struct qcom_wcnss *wcnss,
			    struct qcom_iris *iris,
			    bool use_48mhz_xo)
{
	mutex_lock(&wcnss->iris_lock);

	wcnss->iris = iris;
	wcnss->use_48mhz_xo = use_48mhz_xo;

	mutex_unlock(&wcnss->iris_lock);
}