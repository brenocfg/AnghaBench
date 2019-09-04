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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_rss_config_obj {int /*<<< orphan*/  config_rss; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  raw; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  bnx2x_obj_type ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_init_raw_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_setup_rss ; 

void bnx2x_init_rss_config_obj(struct bnx2x *bp,
			       struct bnx2x_rss_config_obj *rss_obj,
			       u8 cl_id, u32 cid, u8 func_id, u8 engine_id,
			       void *rdata, dma_addr_t rdata_mapping,
			       int state, unsigned long *pstate,
			       bnx2x_obj_type type)
{
	bnx2x_init_raw_obj(&rss_obj->raw, cl_id, cid, func_id, rdata,
			   rdata_mapping, state, pstate, type);

	rss_obj->engine_id  = engine_id;
	rss_obj->config_rss = bnx2x_setup_rss;
}