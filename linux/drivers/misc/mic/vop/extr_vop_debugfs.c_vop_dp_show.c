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
struct vop_info {int /*<<< orphan*/  hotplug_work; struct vop_device* vpdev; } ;
struct vop_device {TYPE_1__* hw_ops; } ;
struct seq_file {struct vop_info* private; } ;
struct mic_vqconfig {int address; int num; int used_address; } ;
struct mic_device_desc {int type; int num_vq; int feature_len; int config_len; int status; } ;
struct mic_device_ctrl {int config_change; int vdev_reset; int guest_ack; int host_ack; int used_address_updated; int vdev; int c2h_vdev_db; int h2c_vdev_db; } ;
struct mic_bootparam {int magic; int h2c_config_db; int node_id; int c2h_scif_db; int h2c_scif_db; int scif_host_dma_addr; int scif_card_dma_addr; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;
struct TYPE_2__ {struct mic_bootparam* (* get_dp ) (struct vop_device*) ;} ;

/* Variables and functions */
 int MIC_DP_SIZE ; 
 int mic_aligned_desc_size (struct mic_device_desc*) ; 
 scalar_t__ mic_total_desc_size (struct mic_device_desc*) ; 
 struct mic_vqconfig* mic_vq_config (struct mic_device_desc*) ; 
 int /*<<< orphan*/ * mic_vq_configspace (struct mic_device_desc*) ; 
 scalar_t__ mic_vq_features (struct mic_device_desc*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct mic_bootparam* stub1 (struct vop_device*) ; 

__attribute__((used)) static int vop_dp_show(struct seq_file *s, void *pos)
{
	struct mic_device_desc *d;
	struct mic_device_ctrl *dc;
	struct mic_vqconfig *vqconfig;
	__u32 *features;
	__u8 *config;
	struct vop_info *vi = s->private;
	struct vop_device *vpdev = vi->vpdev;
	struct mic_bootparam *bootparam = vpdev->hw_ops->get_dp(vpdev);
	int j, k;

	seq_printf(s, "Bootparam: magic 0x%x\n",
		   bootparam->magic);
	seq_printf(s, "Bootparam: h2c_config_db %d\n",
		   bootparam->h2c_config_db);
	seq_printf(s, "Bootparam: node_id %d\n",
		   bootparam->node_id);
	seq_printf(s, "Bootparam: c2h_scif_db %d\n",
		   bootparam->c2h_scif_db);
	seq_printf(s, "Bootparam: h2c_scif_db %d\n",
		   bootparam->h2c_scif_db);
	seq_printf(s, "Bootparam: scif_host_dma_addr 0x%llx\n",
		   bootparam->scif_host_dma_addr);
	seq_printf(s, "Bootparam: scif_card_dma_addr 0x%llx\n",
		   bootparam->scif_card_dma_addr);

	for (j = sizeof(*bootparam);
		j < MIC_DP_SIZE; j += mic_total_desc_size(d)) {
		d = (void *)bootparam + j;
		dc = (void *)d + mic_aligned_desc_size(d);

		/* end of list */
		if (d->type == 0)
			break;

		if (d->type == -1)
			continue;

		seq_printf(s, "Type %d ", d->type);
		seq_printf(s, "Num VQ %d ", d->num_vq);
		seq_printf(s, "Feature Len %d\n", d->feature_len);
		seq_printf(s, "Config Len %d ", d->config_len);
		seq_printf(s, "Shutdown Status %d\n", d->status);

		for (k = 0; k < d->num_vq; k++) {
			vqconfig = mic_vq_config(d) + k;
			seq_printf(s, "vqconfig[%d]: ", k);
			seq_printf(s, "address 0x%llx ",
				   vqconfig->address);
			seq_printf(s, "num %d ", vqconfig->num);
			seq_printf(s, "used address 0x%llx\n",
				   vqconfig->used_address);
		}

		features = (__u32 *)mic_vq_features(d);
		seq_printf(s, "Features: Host 0x%x ", features[0]);
		seq_printf(s, "Guest 0x%x\n", features[1]);

		config = mic_vq_configspace(d);
		for (k = 0; k < d->config_len; k++)
			seq_printf(s, "config[%d]=%d\n", k, config[k]);

		seq_puts(s, "Device control:\n");
		seq_printf(s, "Config Change %d ", dc->config_change);
		seq_printf(s, "Vdev reset %d\n", dc->vdev_reset);
		seq_printf(s, "Guest Ack %d ", dc->guest_ack);
		seq_printf(s, "Host ack %d\n", dc->host_ack);
		seq_printf(s, "Used address updated %d ",
			   dc->used_address_updated);
		seq_printf(s, "Vdev 0x%llx\n", dc->vdev);
		seq_printf(s, "c2h doorbell %d ", dc->c2h_vdev_db);
		seq_printf(s, "h2c doorbell %d\n", dc->h2c_vdev_db);
	}
	schedule_work(&vi->hotplug_work);
	return 0;
}