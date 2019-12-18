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
typedef  size_t u64 ;
struct hisi_sas_port {int id; } ;
struct hisi_sas_itct {void* qw2; void* sas_addr; void* qw0; } ;
struct hisi_sas_device {size_t device_id; int dev_type; struct domain_device* sas_device; } ;
struct hisi_hba {struct hisi_sas_itct* itct; struct device* dev; } ;
struct domain_device {int max_linkrate; int /*<<< orphan*/  sas_addr; struct asd_sas_port* port; } ;
struct device {int dummy; } ;
struct asd_sas_port {int dummy; } ;

/* Variables and functions */
 size_t HISI_SAS_DEV_TYPE_SSP ; 
 int ITCT_HDR_AWT_CONTROL_OFF ; 
 int ITCT_HDR_BUS_INACTIVE_TL_OFF ; 
 size_t ITCT_HDR_DEV_TYPE_OFF ; 
 unsigned long long ITCT_HDR_IT_NEXUS_LOSS_TL_OFF ; 
 int ITCT_HDR_MAX_CONN_RATE_OFF ; 
 int ITCT_HDR_MAX_CONN_TL_OFF ; 
 int ITCT_HDR_PORT_ID_OFF ; 
 int ITCT_HDR_REJ_OPEN_TL_OFF ; 
 int ITCT_HDR_VALID_LINK_NUM_OFF ; 
 int ITCT_HDR_VALID_OFF ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
#define  SAS_EDGE_EXPANDER_DEVICE 130 
#define  SAS_END_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 unsigned long long __swab64 (size_t) ; 
 void* cpu_to_le64 (unsigned long long) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hisi_sas_itct*,int /*<<< orphan*/ ,int) ; 
 struct hisi_sas_port* to_hisi_sas_port (struct asd_sas_port*) ; 

__attribute__((used)) static void setup_itct_v1_hw(struct hisi_hba *hisi_hba,
			     struct hisi_sas_device *sas_dev)
{
	struct domain_device *device = sas_dev->sas_device;
	struct device *dev = hisi_hba->dev;
	u64 qw0, device_id = sas_dev->device_id;
	struct hisi_sas_itct *itct = &hisi_hba->itct[device_id];
	struct asd_sas_port *sas_port = device->port;
	struct hisi_sas_port *port = to_hisi_sas_port(sas_port);
	u64 sas_addr;

	memset(itct, 0, sizeof(*itct));

	/* qw0 */
	qw0 = 0;
	switch (sas_dev->dev_type) {
	case SAS_END_DEVICE:
	case SAS_EDGE_EXPANDER_DEVICE:
	case SAS_FANOUT_EXPANDER_DEVICE:
		qw0 = HISI_SAS_DEV_TYPE_SSP << ITCT_HDR_DEV_TYPE_OFF;
		break;
	default:
		dev_warn(dev, "setup itct: unsupported dev type (%d)\n",
			 sas_dev->dev_type);
	}

	qw0 |= ((1 << ITCT_HDR_VALID_OFF) |
		(1 << ITCT_HDR_AWT_CONTROL_OFF) |
		(device->max_linkrate << ITCT_HDR_MAX_CONN_RATE_OFF) |
		(1 << ITCT_HDR_VALID_LINK_NUM_OFF) |
		(port->id << ITCT_HDR_PORT_ID_OFF));
	itct->qw0 = cpu_to_le64(qw0);

	/* qw1 */
	memcpy(&sas_addr, device->sas_addr, SAS_ADDR_SIZE);
	itct->sas_addr = cpu_to_le64(__swab64(sas_addr));

	/* qw2 */
	itct->qw2 = cpu_to_le64((500ULL << ITCT_HDR_IT_NEXUS_LOSS_TL_OFF) |
				(0xff00ULL << ITCT_HDR_BUS_INACTIVE_TL_OFF) |
				(0xff00ULL << ITCT_HDR_MAX_CONN_TL_OFF) |
				(0xff00ULL << ITCT_HDR_REJ_OPEN_TL_OFF));
}