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
typedef  scalar_t__ u32 ;
struct msdc_host {scalar_t__ base; scalar_t__ top_base; TYPE_1__* dev_comp; } ;
struct TYPE_2__ {scalar_t__ pad_tune_reg; } ;

/* Variables and functions */
 scalar_t__ EMMC_TOP_CMD ; 
 int /*<<< orphan*/  MSDC_PAD_TUNE_CMDRDLY ; 
 int /*<<< orphan*/  PAD_CMD_RXDLY ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void msdc_set_cmd_delay(struct msdc_host *host, u32 value)
{
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	if (host->top_base)
		sdr_set_field(host->top_base + EMMC_TOP_CMD, PAD_CMD_RXDLY,
			      value);
	else
		sdr_set_field(host->base + tune_reg, MSDC_PAD_TUNE_CMDRDLY,
			      value);
}