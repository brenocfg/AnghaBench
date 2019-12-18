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
typedef  scalar_t__ u16 ;
struct gbaudio_module_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  mgmt_connection; } ;
struct gbaudio_data_connection {int* state; TYPE_1__* connection; } ;
struct TYPE_2__ {scalar_t__ hd_cport_id; scalar_t__ intf_cport_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_APBRIDGEA_DIRECTION_TX ; 
 int ENODEV ; 
 int GBAUDIO_CODEC_HWPARAMS ; 
 int GBAUDIO_CODEC_SHUTDOWN ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 struct gbaudio_data_connection* find_data (struct gbaudio_module_info*,int) ; 
 int gb_audio_apbridgea_unregister_cport (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int gb_audio_gb_deactivate_tx (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gbaudio_module_disable_tx(struct gbaudio_module_info *module, int id)
{
	int ret;
	u16 data_cport, cportid, i2s_port;
	int module_state;
	struct gbaudio_data_connection *data;

	/* find the dai */
	data = find_data(module, id);
	if (!data) {
		dev_err(module->dev, "%d:DATA connection missing\n", id);
		return -ENODEV;
	}
	module_state = data->state[SNDRV_PCM_STREAM_PLAYBACK];

	if (module_state > GBAUDIO_CODEC_HWPARAMS) {
		data_cport = data->connection->intf_cport_id;
		ret = gb_audio_gb_deactivate_tx(module->mgmt_connection,
						data_cport);
		if (ret) {
			dev_err_ratelimited(module->dev,
					    "deactivate_tx failed:%d\n", ret);
			return ret;
		}
		dev_dbg(module->dev, "Dynamic deactivate %d DAI\n", data_cport);
		data->state[SNDRV_PCM_STREAM_PLAYBACK] =
			GBAUDIO_CODEC_HWPARAMS;
	}

	if (module_state > GBAUDIO_CODEC_SHUTDOWN) {
		i2s_port = 0;	/* fixed for now */
		cportid = data->connection->hd_cport_id;
		ret = gb_audio_apbridgea_unregister_cport(data->connection,
						i2s_port, cportid,
						AUDIO_APBRIDGEA_DIRECTION_TX);
		if (ret) {
			dev_err_ratelimited(module->dev,
					    "unregister_cport failed:%d\n",
					    ret);
			return ret;
		}
		dev_dbg(module->dev, "Dynamic Unregister %d DAI\n", cportid);
		data->state[SNDRV_PCM_STREAM_PLAYBACK] =
			GBAUDIO_CODEC_SHUTDOWN;
	}

	return 0;
}