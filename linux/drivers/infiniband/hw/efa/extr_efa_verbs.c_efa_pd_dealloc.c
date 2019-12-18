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
typedef  int /*<<< orphan*/  u16 ;
struct efa_dev {int /*<<< orphan*/  edev; } ;
struct efa_com_dealloc_pd_params {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int efa_com_dealloc_pd (int /*<<< orphan*/ *,struct efa_com_dealloc_pd_params*) ; 

__attribute__((used)) static int efa_pd_dealloc(struct efa_dev *dev, u16 pdn)
{
	struct efa_com_dealloc_pd_params params = {
		.pdn = pdn,
	};

	return efa_com_dealloc_pd(&dev->edev, &params);
}