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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  min_cll; int /*<<< orphan*/  max_fall; int /*<<< orphan*/  max_cll; int /*<<< orphan*/  metadata_type; int /*<<< orphan*/  eotf; } ;
struct TYPE_4__ {TYPE_1__ hdmi_type1; } ;
struct drm_connector {TYPE_2__ hdr_sink_metadata; } ;

/* Variables and functions */
 int cea_db_payload_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eotf_supported (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hdr_metadata_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
drm_parse_hdr_metadata_block(struct drm_connector *connector, const u8 *db)
{
	u16 len;

	len = cea_db_payload_len(db);

	connector->hdr_sink_metadata.hdmi_type1.eotf =
						eotf_supported(db);
	connector->hdr_sink_metadata.hdmi_type1.metadata_type =
						hdr_metadata_type(db);

	if (len >= 4)
		connector->hdr_sink_metadata.hdmi_type1.max_cll = db[4];
	if (len >= 5)
		connector->hdr_sink_metadata.hdmi_type1.max_fall = db[5];
	if (len >= 6)
		connector->hdr_sink_metadata.hdmi_type1.min_cll = db[6];
}