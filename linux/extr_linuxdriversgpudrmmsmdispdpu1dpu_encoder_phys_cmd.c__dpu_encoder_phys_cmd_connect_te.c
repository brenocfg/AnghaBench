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
struct dpu_encoder_phys {TYPE_2__* hw_pp; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* connect_external_te ) (TYPE_2__*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_cmd_connect_te (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _dpu_encoder_phys_cmd_connect_te(
		struct dpu_encoder_phys *phys_enc, bool enable)
{
	if (!phys_enc || !phys_enc->hw_pp ||
			!phys_enc->hw_pp->ops.connect_external_te)
		return;

	trace_dpu_enc_phys_cmd_connect_te(DRMID(phys_enc->parent), enable);
	phys_enc->hw_pp->ops.connect_external_te(phys_enc->hw_pp, enable);
}