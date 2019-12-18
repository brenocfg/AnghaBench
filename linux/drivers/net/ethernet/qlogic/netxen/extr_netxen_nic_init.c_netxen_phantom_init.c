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
typedef  int u32 ;
struct netxen_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_CMDPEG_STATE ; 
 int EIO ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int const) ; 
#define  PHAN_INITIALIZE_ACK 130 
#define  PHAN_INITIALIZE_COMPLETE 129 
#define  PHAN_INITIALIZE_FAILED 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int netxen_phantom_init(struct netxen_adapter *adapter, int pegtune_val)
{
	u32 val = 0;
	int retries = 60;

	if (pegtune_val)
		return 0;

	do {
		val = NXRD32(adapter, CRB_CMDPEG_STATE);
		switch (val) {
		case PHAN_INITIALIZE_COMPLETE:
		case PHAN_INITIALIZE_ACK:
			return 0;
		case PHAN_INITIALIZE_FAILED:
			goto out_err;
		default:
			break;
		}

		msleep(500);

	} while (--retries);

	NXWR32(adapter, CRB_CMDPEG_STATE, PHAN_INITIALIZE_FAILED);

out_err:
	dev_warn(&adapter->pdev->dev, "firmware init failed\n");
	return -EIO;
}