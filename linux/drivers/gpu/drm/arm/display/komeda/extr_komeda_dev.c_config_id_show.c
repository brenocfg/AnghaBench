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
union komeda_config_id {int n_layers; int value; scalar_t__ n_richs; int /*<<< orphan*/  n_scalers; int /*<<< orphan*/  n_pipelines; int /*<<< orphan*/  max_line_sz; } ;
struct komeda_pipeline {int n_layers; TYPE_2__** layers; int /*<<< orphan*/  n_scalers; } ;
struct komeda_dev {int /*<<< orphan*/  n_pipelines; struct komeda_pipeline** pipelines; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  config_id ;
struct TYPE_3__ {int /*<<< orphan*/  end; } ;
struct TYPE_4__ {scalar_t__ layer_type; TYPE_1__ hsize_in; } ;

/* Variables and functions */
 scalar_t__ KOMEDA_FMT_RICH_LAYER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct komeda_dev* dev_to_mdev (struct device*) ; 
 int /*<<< orphan*/  memset (union komeda_config_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
config_id_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct komeda_dev *mdev = dev_to_mdev(dev);
	struct komeda_pipeline *pipe = mdev->pipelines[0];
	union komeda_config_id config_id;
	int i;

	memset(&config_id, 0, sizeof(config_id));

	config_id.max_line_sz = pipe->layers[0]->hsize_in.end;
	config_id.n_pipelines = mdev->n_pipelines;
	config_id.n_scalers = pipe->n_scalers;
	config_id.n_layers = pipe->n_layers;
	config_id.n_richs = 0;
	for (i = 0; i < pipe->n_layers; i++) {
		if (pipe->layers[i]->layer_type == KOMEDA_FMT_RICH_LAYER)
			config_id.n_richs++;
	}
	return snprintf(buf, PAGE_SIZE, "0x%08x\n", config_id.value);
}