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
typedef  int u8 ;
struct drm_connector {int* latency_present; int* video_latency; int* audio_latency; int /*<<< orphan*/ * eld; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int,int,int) ; 
 size_t DRM_ELD_SAD_COUNT_CONN_TYPE ; 
 int /*<<< orphan*/  DRM_ELD_SUPPORTS_AI ; 
 int cea_db_payload_len (int const*) ; 

__attribute__((used)) static void
drm_parse_hdmi_vsdb_audio(struct drm_connector *connector, const u8 *db)
{
	u8 len = cea_db_payload_len(db);

	if (len >= 6 && (db[6] & (1 << 7)))
		connector->eld[DRM_ELD_SAD_COUNT_CONN_TYPE] |= DRM_ELD_SUPPORTS_AI;
	if (len >= 8) {
		connector->latency_present[0] = db[8] >> 7;
		connector->latency_present[1] = (db[8] >> 6) & 1;
	}
	if (len >= 9)
		connector->video_latency[0] = db[9];
	if (len >= 10)
		connector->audio_latency[0] = db[10];
	if (len >= 11)
		connector->video_latency[1] = db[11];
	if (len >= 12)
		connector->audio_latency[1] = db[12];

	DRM_DEBUG_KMS("HDMI: latency present %d %d, "
		      "video latency %d %d, "
		      "audio latency %d %d\n",
		      connector->latency_present[0],
		      connector->latency_present[1],
		      connector->video_latency[0],
		      connector->video_latency[1],
		      connector->audio_latency[0],
		      connector->audio_latency[1]);
}