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
struct qib_devdata {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct qib_devdata* dd_from_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_idev (struct ib_device*) ; 

__attribute__((used)) static inline struct qib_devdata *dd_from_ibdev(struct ib_device *ibdev)
{
	return dd_from_dev(to_idev(ibdev));
}