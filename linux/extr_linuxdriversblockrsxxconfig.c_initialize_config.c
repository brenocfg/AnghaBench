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
struct TYPE_4__ {scalar_t__ latency; scalar_t__ count; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int cache_order; TYPE_1__ intr_coal; int /*<<< orphan*/  vendor_id; void* stripe_size; void* block_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
struct rsxx_card_cfg {TYPE_3__ data; TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSXX_CFG_VERSION ; 
 void* RSXX_HW_BLK_SIZE ; 
 int /*<<< orphan*/  RSXX_INTR_COAL_DISABLED ; 
 int /*<<< orphan*/  RSXX_VENDOR_ID_IBM ; 

__attribute__((used)) static void initialize_config(struct rsxx_card_cfg *cfg)
{
	cfg->hdr.version = RSXX_CFG_VERSION;

	cfg->data.block_size        = RSXX_HW_BLK_SIZE;
	cfg->data.stripe_size       = RSXX_HW_BLK_SIZE;
	cfg->data.vendor_id         = RSXX_VENDOR_ID_IBM;
	cfg->data.cache_order       = (-1);
	cfg->data.intr_coal.mode    = RSXX_INTR_COAL_DISABLED;
	cfg->data.intr_coal.count   = 0;
	cfg->data.intr_coal.latency = 0;
}