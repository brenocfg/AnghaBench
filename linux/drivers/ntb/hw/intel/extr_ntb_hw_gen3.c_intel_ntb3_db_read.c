#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ntb_dev {int dummy; } ;
struct intel_ntb_dev {TYPE_1__* self_reg; scalar_t__ self_mmio; } ;
struct TYPE_2__ {scalar_t__ db_clear; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndev_db_read (struct intel_ntb_dev*,scalar_t__) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

__attribute__((used)) static u64 intel_ntb3_db_read(struct ntb_dev *ntb)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);

	return ndev_db_read(ndev,
			    ndev->self_mmio +
			    ndev->self_reg->db_clear);
}