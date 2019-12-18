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
struct domain_device {int linkrate; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  dev_type; struct asd_sas_port* port; struct domain_device* parent; } ;
struct device {int dummy; } ;
struct asd_sas_port {int dummy; } ;

/* Variables and functions */
 size_t HISI_SAS_DEV_TYPE_SATA ; 
 size_t HISI_SAS_DEV_TYPE_SSP ; 
 size_t HISI_SAS_DEV_TYPE_STP ; 
 int ITCT_HDR_AWT_CONTINUE_OFF ; 
 int ITCT_HDR_BITLT_OFF ; 
 size_t ITCT_HDR_DEV_TYPE_OFF ; 
 unsigned long long ITCT_HDR_INLT_OFF ; 
 int ITCT_HDR_MCR_OFF ; 
 int ITCT_HDR_MCTLT_OFF ; 
 int ITCT_HDR_PORT_ID_OFF ; 
 int ITCT_HDR_RTOLT_OFF ; 
 int ITCT_HDR_SMP_TIMEOUT ; 
 int ITCT_HDR_SMP_TIMEOUT_OFF ; 
 int ITCT_HDR_VALID_OFF ; 
 int ITCT_HDR_VLN_OFF ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
#define  SAS_EDGE_EXPANDER_DEVICE 132 
#define  SAS_END_DEVICE 131 
#define  SAS_FANOUT_EXPANDER_DEVICE 130 
#define  SAS_SATA_DEV 129 
#define  SAS_SATA_PENDING 128 
 unsigned long long __swab64 (size_t) ; 
 void* cpu_to_le64 (unsigned long long) ; 
 int /*<<< orphan*/  dev_is_expander (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hisi_sas_itct*,int /*<<< orphan*/ ,int) ; 
 struct hisi_sas_port* to_hisi_sas_port (struct asd_sas_port*) ; 

__attribute__((used)) static void setup_itct_v2_hw(struct hisi_hba *hisi_hba,
			     struct hisi_sas_device *sas_dev)
{
	struct domain_device *device = sas_dev->sas_device;
	struct device *dev = hisi_hba->dev;
	u64 qw0, device_id = sas_dev->device_id;
	struct hisi_sas_itct *itct = &hisi_hba->itct[device_id];
	struct domain_device *parent_dev = device->parent;
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
	case SAS_SATA_DEV:
	case SAS_SATA_PENDING:
		if (parent_dev && dev_is_expander(parent_dev->dev_type))
			qw0 = HISI_SAS_DEV_TYPE_STP << ITCT_HDR_DEV_TYPE_OFF;
		else
			qw0 = HISI_SAS_DEV_TYPE_SATA << ITCT_HDR_DEV_TYPE_OFF;
		break;
	default:
		dev_warn(dev, "setup itct: unsupported dev type (%d)\n",
			 sas_dev->dev_type);
	}

	qw0 |= ((1 << ITCT_HDR_VALID_OFF) |
		(device->linkrate << ITCT_HDR_MCR_OFF) |
		(1 << ITCT_HDR_VLN_OFF) |
		(ITCT_HDR_SMP_TIMEOUT << ITCT_HDR_SMP_TIMEOUT_OFF) |
		(1 << ITCT_HDR_AWT_CONTINUE_OFF) |
		(port->id << ITCT_HDR_PORT_ID_OFF));
	itct->qw0 = cpu_to_le64(qw0);

	/* qw1 */
	memcpy(&sas_addr, device->sas_addr, SAS_ADDR_SIZE);
	itct->sas_addr = cpu_to_le64(__swab64(sas_addr));

	/* qw2 */
	if (!dev_is_sata(device))
		itct->qw2 = cpu_to_le64((5000ULL << ITCT_HDR_INLT_OFF) |
					(0x1ULL << ITCT_HDR_BITLT_OFF) |
					(0x32ULL << ITCT_HDR_MCTLT_OFF) |
					(0x1ULL << ITCT_HDR_RTOLT_OFF));
}