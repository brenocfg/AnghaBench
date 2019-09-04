#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct dpu_mdss_cfg {scalar_t__ hwversion; } ;
struct TYPE_3__ {scalar_t__ hw_rev; int /*<<< orphan*/  (* cfg_init ) (struct dpu_mdss_cfg*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dpu_mdss_cfg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* cfg_handler ; 
 int /*<<< orphan*/  dpu_hw_catalog_deinit (struct dpu_mdss_cfg*) ; 
 struct dpu_mdss_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpu_mdss_cfg*) ; 

struct dpu_mdss_cfg *dpu_hw_catalog_init(u32 hw_rev)
{
	int i;
	struct dpu_mdss_cfg *dpu_cfg;

	dpu_cfg = kzalloc(sizeof(*dpu_cfg), GFP_KERNEL);
	if (!dpu_cfg)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < ARRAY_SIZE(cfg_handler); i++) {
		if (cfg_handler[i].hw_rev == hw_rev) {
			cfg_handler[i].cfg_init(dpu_cfg);
			dpu_cfg->hwversion = hw_rev;
			return dpu_cfg;
		}
	}

	DPU_ERROR("unsupported chipset id:%X\n", hw_rev);
	dpu_hw_catalog_deinit(dpu_cfg);
	return ERR_PTR(-ENODEV);
}