#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipr_ioa_cfg {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ raw; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; TYPE_2__ u; } ;
struct ipr_hostrcb {TYPE_3__ hcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_log_hex_data (struct ipr_ioa_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_log_generic_error(struct ipr_ioa_cfg *ioa_cfg,
				  struct ipr_hostrcb *hostrcb)
{
	ipr_log_hex_data(ioa_cfg, hostrcb->hcam.u.raw.data,
			 be32_to_cpu(hostrcb->hcam.length));
}