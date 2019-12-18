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
struct sii8620 {int sink_detected; int feature_complete; int /*<<< orphan*/ * edid; int /*<<< orphan*/  sink_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINK_NONE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii8620_disable_hpd (struct sii8620*) ; 

__attribute__((used)) static void sii8620_hpd_unplugged(struct sii8620 *ctx)
{
	sii8620_disable_hpd(ctx);
	ctx->sink_type = SINK_NONE;
	ctx->sink_detected = false;
	ctx->feature_complete = false;
	kfree(ctx->edid);
	ctx->edid = NULL;
}