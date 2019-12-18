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
struct TYPE_3__ {int /*<<< orphan*/  debugfs_entry; } ;
struct hva_dev {int instance_id; TYPE_1__ dbg; } ;
struct TYPE_4__ {int /*<<< orphan*/  debugfs_entry; void* min_bitrate; void* min_period; void* min_duration; } ;
struct hva_ctx {TYPE_2__ dbg; struct hva_dev* hva_dev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 void* UINT_MAX ; 
 int /*<<< orphan*/  ctx_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hva_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void hva_dbg_ctx_create(struct hva_ctx *ctx)
{
	struct hva_dev *hva = ctx->hva_dev;
	char name[4] = "";

	ctx->dbg.min_duration = UINT_MAX;
	ctx->dbg.min_period = UINT_MAX;
	ctx->dbg.min_bitrate = UINT_MAX;

	snprintf(name, sizeof(name), "%d", hva->instance_id);

	ctx->dbg.debugfs_entry = debugfs_create_file(name, 0444,
						     hva->dbg.debugfs_entry,
						     ctx, &ctx_fops);
}