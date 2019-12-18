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
struct snd_soc_dapm_widget {scalar_t__ id; int /*<<< orphan*/  name; int /*<<< orphan*/  sname; } ;
struct gbaudio_module_info {int /*<<< orphan*/  dev; } ;
struct gbaudio_codec_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int NAME_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gbaudio_module_disable_rx (struct gbaudio_module_info*,int) ; 
 int gbaudio_module_disable_tx (struct gbaudio_module_info*,int) ; 
 int gbaudio_module_enable_rx (struct gbaudio_codec_info*,struct gbaudio_module_info*,int) ; 
 int gbaudio_module_enable_tx (struct gbaudio_codec_info*,struct gbaudio_module_info*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_soc_dapm_aif_in ; 
 scalar_t__ snd_soc_dapm_aif_out ; 
 int sscanf (int /*<<< orphan*/ ,char*,char*,int*,char*) ; 

int gbaudio_module_update(struct gbaudio_codec_info *codec,
			  struct snd_soc_dapm_widget *w,
			  struct gbaudio_module_info *module, int enable)
{
	int dai_id, ret;
	char intf_name[NAME_SIZE], dir[NAME_SIZE];

	dev_dbg(module->dev, "%s:Module update %s sequence\n", w->name,
		enable ? "Enable" : "Disable");

	if ((w->id != snd_soc_dapm_aif_in) && (w->id != snd_soc_dapm_aif_out)) {
		dev_dbg(codec->dev, "No action required for %s\n", w->name);
		return 0;
	}

	/* parse dai_id from AIF widget's stream_name */
	ret = sscanf(w->sname, "%s %d %s", intf_name, &dai_id, dir);
	if (ret < 3) {
		dev_err(codec->dev, "Error while parsing dai_id for %s\n",
			w->name);
		return -EINVAL;
	}

	mutex_lock(&codec->lock);
	if (w->id == snd_soc_dapm_aif_in) {
		if (enable)
			ret = gbaudio_module_enable_tx(codec, module, dai_id);
		else
			ret = gbaudio_module_disable_tx(module, dai_id);
	} else if (w->id == snd_soc_dapm_aif_out) {
		if (enable)
			ret = gbaudio_module_enable_rx(codec, module, dai_id);
		else
			ret = gbaudio_module_disable_rx(module, dai_id);
	}

	mutex_unlock(&codec->lock);

	return ret;
}