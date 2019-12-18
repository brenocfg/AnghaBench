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
struct siw_device {int /*<<< orphan*/  mem_xa; int /*<<< orphan*/  qp_xa; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct siw_device* to_siw_dev (struct ib_device*) ; 
 int /*<<< orphan*/  xa_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_device_cleanup(struct ib_device *base_dev)
{
	struct siw_device *sdev = to_siw_dev(base_dev);

	xa_destroy(&sdev->qp_xa);
	xa_destroy(&sdev->mem_xa);
}