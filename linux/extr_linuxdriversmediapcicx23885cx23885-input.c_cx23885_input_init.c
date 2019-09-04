#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int version; int /*<<< orphan*/  product; scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct cx23885_kernel_ir* priv; int /*<<< orphan*/  allowed_protocols; TYPE_2__ dev; TYPE_1__ input_id; struct cx23885_kernel_ir* input_phys; struct cx23885_kernel_ir* device_name; } ;
struct cx23885_kernel_ir {struct cx23885_kernel_ir* name; struct cx23885_kernel_ir* phys; struct rc_dev* rc; struct cx23885_dev* cx; } ;
struct cx23885_dev {int board; struct cx23885_kernel_ir* kernel_ir; TYPE_3__* pci; int /*<<< orphan*/ * sd_ir; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ vendor; int /*<<< orphan*/  subsystem_device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PCI ; 
#define  CX23885_BOARD_DVBSKY_S950 144 
#define  CX23885_BOARD_DVBSKY_S950C 143 
#define  CX23885_BOARD_DVBSKY_S952 142 
#define  CX23885_BOARD_DVBSKY_T9580 141 
#define  CX23885_BOARD_DVBSKY_T980C 140 
#define  CX23885_BOARD_DVBSKY_T982 139 
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 138 
#define  CX23885_BOARD_HAUPPAUGE_HVR1265_K4 137 
#define  CX23885_BOARD_HAUPPAUGE_HVR1270 136 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 135 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 134 
#define  CX23885_BOARD_MYGICA_X8507 133 
#define  CX23885_BOARD_TBS_6980 132 
#define  CX23885_BOARD_TBS_6981 131 
#define  CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL 130 
#define  CX23885_BOARD_TEVII_S470 129 
#define  CX23885_BOARD_TT_CT2_4500_CI 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 char* RC_MAP_DVBSKY ; 
 char* RC_MAP_HAUPPAUGE ; 
 char* RC_MAP_NEC_TERRATEC_CINERGY_XS ; 
 char* RC_MAP_TBS_NEC ; 
 char* RC_MAP_TEVII_NEC ; 
 char* RC_MAP_TOTAL_MEDIA_IN_HAND_02 ; 
 char* RC_MAP_TT_1500 ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 TYPE_4__* cx23885_boards ; 
 int /*<<< orphan*/  cx23885_input_ir_close ; 
 int /*<<< orphan*/  cx23885_input_ir_open ; 
 int /*<<< orphan*/  cx23885_input_ir_stop (struct cx23885_dev*) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx23885_kernel_ir*) ; 
 struct cx23885_kernel_ir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (TYPE_3__*) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 

int cx23885_input_init(struct cx23885_dev *dev)
{
	struct cx23885_kernel_ir *kernel_ir;
	struct rc_dev *rc;
	char *rc_map;
	u64 allowed_protos;

	int ret;

	/*
	 * If the IR device (hardware registers, chip, GPIO lines, etc.) isn't
	 * encapsulated in a v4l2_subdev, then I'm not going to deal with it.
	 */
	if (dev->sd_ir == NULL)
		return -ENODEV;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1270:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
	case CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
		/* Integrated CX2388[58] IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* The grey Hauppauge RC-5 remote */
		rc_map = RC_MAP_HAUPPAUGE;
		break;
	case CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* The grey Terratec remote with orange buttons */
		rc_map = RC_MAP_NEC_TERRATEC_CINERGY_XS;
		break;
	case CX23885_BOARD_TEVII_S470:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TEVII_NEC;
		break;
	case CX23885_BOARD_MYGICA_X8507:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TOTAL_MEDIA_IN_HAND_02;
		break;
	case CX23885_BOARD_TBS_6980:
	case CX23885_BOARD_TBS_6981:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TBS_NEC;
		break;
	case CX23885_BOARD_DVBSKY_T9580:
	case CX23885_BOARD_DVBSKY_T980C:
	case CX23885_BOARD_DVBSKY_S950C:
	case CX23885_BOARD_DVBSKY_S950:
	case CX23885_BOARD_DVBSKY_S952:
	case CX23885_BOARD_DVBSKY_T982:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		rc_map = RC_MAP_DVBSKY;
		break;
	case CX23885_BOARD_TT_CT2_4500_CI:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		rc_map = RC_MAP_TT_1500;
		break;
	default:
		return -ENODEV;
	}

	/* cx23885 board instance kernel IR state */
	kernel_ir = kzalloc(sizeof(struct cx23885_kernel_ir), GFP_KERNEL);
	if (kernel_ir == NULL)
		return -ENOMEM;

	kernel_ir->cx = dev;
	kernel_ir->name = kasprintf(GFP_KERNEL, "cx23885 IR (%s)",
				    cx23885_boards[dev->board].name);
	if (!kernel_ir->name) {
		ret = -ENOMEM;
		goto err_out_free;
	}

	kernel_ir->phys = kasprintf(GFP_KERNEL, "pci-%s/ir0",
				    pci_name(dev->pci));
	if (!kernel_ir->phys) {
		ret = -ENOMEM;
		goto err_out_free_name;
	}

	/* input device */
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rc) {
		ret = -ENOMEM;
		goto err_out_free_phys;
	}

	kernel_ir->rc = rc;
	rc->device_name = kernel_ir->name;
	rc->input_phys = kernel_ir->phys;
	rc->input_id.bustype = BUS_PCI;
	rc->input_id.version = 1;
	if (dev->pci->subsystem_vendor) {
		rc->input_id.vendor  = dev->pci->subsystem_vendor;
		rc->input_id.product = dev->pci->subsystem_device;
	} else {
		rc->input_id.vendor  = dev->pci->vendor;
		rc->input_id.product = dev->pci->device;
	}
	rc->dev.parent = &dev->pci->dev;
	rc->allowed_protocols = allowed_protos;
	rc->priv = kernel_ir;
	rc->open = cx23885_input_ir_open;
	rc->close = cx23885_input_ir_close;
	rc->map_name = rc_map;
	rc->driver_name = MODULE_NAME;

	/* Go */
	dev->kernel_ir = kernel_ir;
	ret = rc_register_device(rc);
	if (ret)
		goto err_out_stop;

	return 0;

err_out_stop:
	cx23885_input_ir_stop(dev);
	dev->kernel_ir = NULL;
	rc_free_device(rc);
err_out_free_phys:
	kfree(kernel_ir->phys);
err_out_free_name:
	kfree(kernel_ir->name);
err_out_free:
	kfree(kernel_ir);
	return ret;
}