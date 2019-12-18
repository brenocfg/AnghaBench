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
struct dce_hwseq {TYPE_3__* ctx; } ;
struct TYPE_6__ {TYPE_2__* dc; int /*<<< orphan*/  logger; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hubp_pg_control ) (struct dce_hwseq*,int,int) ;int /*<<< orphan*/  (* dpp_pg_control ) (struct dce_hwseq*,int,int) ;} ;
struct TYPE_5__ {TYPE_1__ hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_IP_REQUEST_CNTL ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DEBUG (char*,int) ; 
 int /*<<< orphan*/  IP_REQUEST_EN ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dce_hwseq*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct dce_hwseq*,int,int) ; 

__attribute__((used)) static void power_on_plane(
	struct dce_hwseq *hws,
	int plane_id)
{
	DC_LOGGER_INIT(hws->ctx->logger);
	if (REG(DC_IP_REQUEST_CNTL)) {
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);
		hws->ctx->dc->hwss.dpp_pg_control(hws, plane_id, true);
		hws->ctx->dc->hwss.hubp_pg_control(hws, plane_id, true);
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Un-gated front end for pipe %d\n", plane_id);
	}
}