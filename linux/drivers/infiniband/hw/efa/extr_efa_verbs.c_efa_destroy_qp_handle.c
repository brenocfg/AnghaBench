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
typedef  int /*<<< orphan*/  u32 ;
struct efa_dev {int /*<<< orphan*/  edev; } ;
struct efa_com_destroy_qp_params {int /*<<< orphan*/  qp_handle; } ;

/* Variables and functions */
 int efa_com_destroy_qp (int /*<<< orphan*/ *,struct efa_com_destroy_qp_params*) ; 

__attribute__((used)) static int efa_destroy_qp_handle(struct efa_dev *dev, u32 qp_handle)
{
	struct efa_com_destroy_qp_params params = { .qp_handle = qp_handle };

	return efa_com_destroy_qp(&dev->edev, &params);
}