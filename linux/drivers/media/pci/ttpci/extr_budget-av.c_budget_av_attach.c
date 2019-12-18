#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct saa7146_pci_extension_data {int dummy; } ;
struct saa7146_dev {struct budget_av* ext_priv; } ;
struct TYPE_8__ {struct budget_av* priv; int /*<<< orphan*/  num; int /*<<< orphan*/ * proposed_mac; } ;
struct TYPE_10__ {TYPE_2__ dvb_adapter; int /*<<< orphan*/  i2c_adap; scalar_t__ ci_present; } ;
struct budget_av {int has_saa7113; TYPE_4__ budget; int /*<<< orphan*/  vd; } ;
struct TYPE_7__ {int /*<<< orphan*/  vidioc_s_input; int /*<<< orphan*/  vidioc_g_input; int /*<<< orphan*/  vidioc_enum_input; } ;
struct TYPE_9__ {TYPE_1__ vid_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD1_INIT ; 
 int /*<<< orphan*/  DD1_STREAM_B ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  PCI_BT_V1 ; 
 int /*<<< orphan*/  SAA7146_HPS_SOURCE_PORT_A ; 
 int /*<<< orphan*/  SAA7146_HPS_SYNC_PORT_A ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  ciintf_init (struct budget_av*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct saa7146_dev*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frontend_init (struct budget_av*) ; 
 scalar_t__ i2c_readregs (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct budget_av*) ; 
 struct budget_av* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ saa7113_init (struct budget_av*) ; 
 int /*<<< orphan*/  saa7113_setinput (struct budget_av*,int /*<<< orphan*/ ) ; 
 int saa7146_register_device (int /*<<< orphan*/ *,struct saa7146_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_set_hps_source_and_sync (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa7146_vv_init (struct saa7146_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  saa7146_vv_release (struct saa7146_dev*) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int ttpci_budget_init (TYPE_4__*,struct saa7146_dev*,struct saa7146_pci_extension_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_init_hooks (TYPE_4__*) ; 
 int /*<<< orphan*/  vidioc_enum_input ; 
 int /*<<< orphan*/  vidioc_g_input ; 
 int /*<<< orphan*/  vidioc_s_input ; 
 TYPE_3__ vv_data ; 

__attribute__((used)) static int budget_av_attach(struct saa7146_dev *dev, struct saa7146_pci_extension_data *info)
{
	struct budget_av *budget_av;
	u8 *mac;
	int err;

	dprintk(2, "dev: %p\n", dev);

	if (!(budget_av = kzalloc(sizeof(struct budget_av), GFP_KERNEL)))
		return -ENOMEM;

	budget_av->has_saa7113 = 0;
	budget_av->budget.ci_present = 0;

	dev->ext_priv = budget_av;

	err = ttpci_budget_init(&budget_av->budget, dev, info, THIS_MODULE,
				adapter_nr);
	if (err) {
		kfree(budget_av);
		return err;
	}

	/* knc1 initialization */
	saa7146_write(dev, DD1_STREAM_B, 0x04000000);
	saa7146_write(dev, DD1_INIT, 0x07000600);
	saa7146_write(dev, MC2, MASK_09 | MASK_25 | MASK_10 | MASK_26);

	if (saa7113_init(budget_av) == 0) {
		budget_av->has_saa7113 = 1;
		err = saa7146_vv_init(dev, &vv_data);
		if (err != 0) {
			/* fixme: proper cleanup here */
			ERR("cannot init vv subsystem\n");
			return err;
		}
		vv_data.vid_ops.vidioc_enum_input = vidioc_enum_input;
		vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
		vv_data.vid_ops.vidioc_s_input = vidioc_s_input;

		if ((err = saa7146_register_device(&budget_av->vd, dev, "knc1", VFL_TYPE_GRABBER))) {
			/* fixme: proper cleanup here */
			ERR("cannot register capture v4l2 device\n");
			saa7146_vv_release(dev);
			return err;
		}

		/* beware: this modifies dev->vv ... */
		saa7146_set_hps_source_and_sync(dev, SAA7146_HPS_SOURCE_PORT_A,
						SAA7146_HPS_SYNC_PORT_A);

		saa7113_setinput(budget_av, 0);
	}

	/* fixme: find some sane values here... */
	saa7146_write(dev, PCI_BT_V1, 0x1c00101f);

	mac = budget_av->budget.dvb_adapter.proposed_mac;
	if (i2c_readregs(&budget_av->budget.i2c_adap, 0xa0, 0x30, mac, 6)) {
		pr_err("KNC1-%d: Could not read MAC from KNC1 card\n",
		       budget_av->budget.dvb_adapter.num);
		eth_zero_addr(mac);
	} else {
		pr_info("KNC1-%d: MAC addr = %pM\n",
			budget_av->budget.dvb_adapter.num, mac);
	}

	budget_av->budget.dvb_adapter.priv = budget_av;
	frontend_init(budget_av);
	ciintf_init(budget_av);

	ttpci_budget_init_hooks(&budget_av->budget);

	return 0;
}