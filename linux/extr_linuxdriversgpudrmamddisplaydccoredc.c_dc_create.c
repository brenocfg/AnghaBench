#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dc_init_data {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int disable_dfs_bypass; } ;
struct TYPE_9__ {int /*<<< orphan*/  dmcu_version; int /*<<< orphan*/  dc_ver; } ;
struct TYPE_8__ {int linear_pitch_alignment; int /*<<< orphan*/  max_audios; int /*<<< orphan*/  max_links; int /*<<< orphan*/  max_streams; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* init_hw ) (struct dc*) ;} ;
struct dc {TYPE_6__ debug; int /*<<< orphan*/  config; TYPE_5__* res_pool; TYPE_3__ versions; TYPE_2__ caps; int /*<<< orphan*/  link_count; TYPE_1__ hwss; } ;
struct TYPE_11__ {unsigned int pipe_count; scalar_t__ underlay_pipe_index; TYPE_4__* dmcu; int /*<<< orphan*/  audio_count; int /*<<< orphan*/  stream_enc_count; } ;
struct TYPE_10__ {int /*<<< orphan*/  dmcu_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_DC (char*) ; 
 int /*<<< orphan*/  DC_VER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NO_UNDERLAY_PIPE ; 
 int construct (struct dc*,struct dc_init_data const*) ; 
 int /*<<< orphan*/  kfree (struct dc*) ; 
 struct dc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dc*) ; 

struct dc *dc_create(const struct dc_init_data *init_params)
{
	struct dc *dc = kzalloc(sizeof(*dc), GFP_KERNEL);
	unsigned int full_pipe_count;

	if (NULL == dc)
		goto alloc_fail;

	if (false == construct(dc, init_params))
		goto construct_fail;

	/*TODO: separate HW and SW initialization*/
	dc->hwss.init_hw(dc);

	full_pipe_count = dc->res_pool->pipe_count;
	if (dc->res_pool->underlay_pipe_index != NO_UNDERLAY_PIPE)
		full_pipe_count--;
	dc->caps.max_streams = min(
			full_pipe_count,
			dc->res_pool->stream_enc_count);

	dc->caps.max_links = dc->link_count;
	dc->caps.max_audios = dc->res_pool->audio_count;
	dc->caps.linear_pitch_alignment = 64;

	/* Populate versioning information */
	dc->versions.dc_ver = DC_VER;

	if (dc->res_pool->dmcu != NULL)
		dc->versions.dmcu_version = dc->res_pool->dmcu->dmcu_version;

	dc->config = init_params->flags;

	DC_LOG_DC("Display Core initialized\n");


	/* TODO: missing feature to be enabled */
	dc->debug.disable_dfs_bypass = true;

	return dc;

construct_fail:
	kfree(dc);

alloc_fail:
	return NULL;
}