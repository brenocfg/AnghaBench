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
typedef  int u32 ;
struct intel_sdvo_tv_format {int dummy; } ;
struct intel_sdvo {int dummy; } ;
struct TYPE_2__ {int mode; } ;
struct drm_connector_state {TYPE_1__ tv; } ;
typedef  int /*<<< orphan*/  format_map ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SDVO_CMD_SET_TV_FORMAT ; 
 int intel_sdvo_set_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_tv_format*,int) ; 
 int /*<<< orphan*/  memcpy (struct intel_sdvo_tv_format*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct intel_sdvo_tv_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static bool intel_sdvo_set_tv_format(struct intel_sdvo *intel_sdvo,
				     const struct drm_connector_state *conn_state)
{
	struct intel_sdvo_tv_format format;
	u32 format_map;

	format_map = 1 << conn_state->tv.mode;
	memset(&format, 0, sizeof(format));
	memcpy(&format, &format_map, min(sizeof(format), sizeof(format_map)));

	BUILD_BUG_ON(sizeof(format) != 6);
	return intel_sdvo_set_value(intel_sdvo,
				    SDVO_CMD_SET_TV_FORMAT,
				    &format, sizeof(format));
}