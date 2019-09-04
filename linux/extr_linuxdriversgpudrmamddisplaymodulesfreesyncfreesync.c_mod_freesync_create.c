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
struct persistent_data_flag {int save_per_edid; int save_per_link; } ;
struct mod_freesync {int dummy; } ;
struct freesync_entity {int dummy; } ;
struct dc {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int drr_internal_supported; int drr_external_supported; int lcd_freesync_default_set; int lcd_freesync_default_value; } ;
struct core_freesync {struct core_freesync* map; struct mod_freesync public; TYPE_1__ opts; struct dc* dc; scalar_t__ num_entities; int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  FREESYNC_DEFAULT_REGKEY ; 
 int /*<<< orphan*/  FREESYNC_NO_STATIC_FOR_EXTERNAL_DP_REGKEY ; 
 int /*<<< orphan*/  FREESYNC_NO_STATIC_FOR_INTERNAL_REGKEY ; 
 int /*<<< orphan*/  FREESYNC_REGISTRY_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MOD_FREESYNC_MAX_CONCURRENT_STREAMS ; 
 scalar_t__ dm_read_persistent_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,struct persistent_data_flag*) ; 
 int /*<<< orphan*/  dm_write_persistent_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct persistent_data_flag*) ; 
 struct core_freesync* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct core_freesync*) ; 
 struct core_freesync* kzalloc (int,int /*<<< orphan*/ ) ; 

struct mod_freesync *mod_freesync_create(struct dc *dc)
{
	struct core_freesync *core_freesync =
			kzalloc(sizeof(struct core_freesync), GFP_KERNEL);


	struct persistent_data_flag flag;

	int i, data = 0;

	if (core_freesync == NULL)
		goto fail_alloc_context;

	core_freesync->map = kcalloc(MOD_FREESYNC_MAX_CONCURRENT_STREAMS,
					sizeof(struct freesync_entity),
					GFP_KERNEL);

	if (core_freesync->map == NULL)
		goto fail_alloc_map;

	for (i = 0; i < MOD_FREESYNC_MAX_CONCURRENT_STREAMS; i++)
		core_freesync->map[i].stream = NULL;

	core_freesync->num_entities = 0;

	if (dc == NULL)
		goto fail_construct;

	core_freesync->dc = dc;

	/* Create initial module folder in registry for freesync enable data */
	flag.save_per_edid = true;
	flag.save_per_link = false;
	dm_write_persistent_data(dc->ctx, NULL, FREESYNC_REGISTRY_NAME,
			NULL, NULL, 0, &flag);
	flag.save_per_edid = false;
	flag.save_per_link = false;

	if (dm_read_persistent_data(dc->ctx, NULL, NULL,
			FREESYNC_NO_STATIC_FOR_INTERNAL_REGKEY,
			&data, sizeof(data), &flag)) {
		core_freesync->opts.drr_internal_supported =
			(data & 1) ? false : true;
	}

	if (dm_read_persistent_data(dc->ctx, NULL, NULL,
			FREESYNC_NO_STATIC_FOR_EXTERNAL_DP_REGKEY,
			&data, sizeof(data), &flag)) {
		core_freesync->opts.drr_external_supported =
				(data & 1) ? false : true;
	}

	if (dm_read_persistent_data(dc->ctx, NULL, NULL,
			FREESYNC_DEFAULT_REGKEY,
			&data, sizeof(data), &flag)) {
		core_freesync->opts.lcd_freesync_default_set = true;
		core_freesync->opts.lcd_freesync_default_value = data;
	} else {
		core_freesync->opts.lcd_freesync_default_set = false;
		core_freesync->opts.lcd_freesync_default_value = 0;
	}

	return &core_freesync->public;

fail_construct:
	kfree(core_freesync->map);

fail_alloc_map:
	kfree(core_freesync);

fail_alloc_context:
	return NULL;
}