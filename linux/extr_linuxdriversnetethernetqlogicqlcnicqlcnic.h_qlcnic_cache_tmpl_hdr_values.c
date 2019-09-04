#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_fw_dump {int dummy; } ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_4__ {TYPE_1__* hw_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cache_tmpl_hdr_values ) (struct qlcnic_fw_dump*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct qlcnic_fw_dump*) ; 

__attribute__((used)) static inline void qlcnic_cache_tmpl_hdr_values(struct qlcnic_adapter *adapter,
						struct qlcnic_fw_dump *fw_dump)
{
	adapter->ahw->hw_ops->cache_tmpl_hdr_values(fw_dump);
}