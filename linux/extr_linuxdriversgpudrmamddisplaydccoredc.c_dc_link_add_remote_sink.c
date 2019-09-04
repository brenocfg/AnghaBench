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
typedef  int /*<<< orphan*/  uint8_t ;
struct dc_sink_init_data {int /*<<< orphan*/  link; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/  raw_edid; } ;
struct dc_sink {TYPE_1__ dc_edid; int /*<<< orphan*/  edid_caps; } ;
struct dc_link {int /*<<< orphan*/  ctx; } ;
typedef  enum dc_edid_status { ____Placeholder_dc_edid_status } dc_edid_status ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int DC_MAX_EDID_BUFFER_SIZE ; 
 int EDID_OK ; 
 struct dc_sink* dc_sink_create (struct dc_sink_init_data*) ; 
 int /*<<< orphan*/  dc_sink_release (struct dc_sink*) ; 
 int /*<<< orphan*/  dm_error (char*,...) ; 
 int dm_helpers_parse_edid_caps (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_add_remote_sink_helper (struct dc_link*,struct dc_sink*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

struct dc_sink *dc_link_add_remote_sink(
		struct dc_link *link,
		const uint8_t *edid,
		int len,
		struct dc_sink_init_data *init_data)
{
	struct dc_sink *dc_sink;
	enum dc_edid_status edid_status;

	if (len > DC_MAX_EDID_BUFFER_SIZE) {
		dm_error("Max EDID buffer size breached!\n");
		return NULL;
	}

	if (!init_data) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	if (!init_data->link) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dc_sink = dc_sink_create(init_data);

	if (!dc_sink)
		return NULL;

	memmove(dc_sink->dc_edid.raw_edid, edid, len);
	dc_sink->dc_edid.length = len;

	if (!link_add_remote_sink_helper(
			link,
			dc_sink))
		goto fail_add_sink;

	edid_status = dm_helpers_parse_edid_caps(
			link->ctx,
			&dc_sink->dc_edid,
			&dc_sink->edid_caps);

	/*
	 * Treat device as no EDID device if EDID
	 * parsing fails
	 */
	if (edid_status != EDID_OK) {
		dc_sink->dc_edid.length = 0;
		dm_error("Bad EDID, status%d!\n", edid_status);
	}

	return dc_sink;

fail_add_sink:
	dc_sink_release(dc_sink);
	return NULL;
}