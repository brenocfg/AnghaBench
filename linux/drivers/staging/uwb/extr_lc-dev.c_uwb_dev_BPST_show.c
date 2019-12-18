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
typedef  int u16 ;
struct uwb_dev {struct uwb_beca_e* bce; } ;
struct uwb_beca_e {int /*<<< orphan*/  mutex; TYPE_1__* be; } ;
struct uwb_beacon_frame {int Beacon_Slot_Number; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int wBPSTOffset; scalar_t__ BeaconInfo; } ;

/* Variables and functions */
 int UWB_BEACON_SLOT_LENGTH_US ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 

__attribute__((used)) static ssize_t uwb_dev_BPST_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);
	struct uwb_beca_e *bce;
	struct uwb_beacon_frame *bf;
	u16 bpst;

	bce = uwb_dev->bce;
	mutex_lock(&bce->mutex);
	bf = (struct uwb_beacon_frame *)bce->be->BeaconInfo;
	bpst = bce->be->wBPSTOffset
		- (u16)(bf->Beacon_Slot_Number * UWB_BEACON_SLOT_LENGTH_US);
	mutex_unlock(&bce->mutex);

	return sprintf(buf, "%d\n", bpst);
}