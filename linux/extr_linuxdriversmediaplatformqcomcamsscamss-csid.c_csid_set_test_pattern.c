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
struct csid_testgen_config {int enabled; int /*<<< orphan*/  payload_mode; } ;
struct csid_device {int /*<<< orphan*/ * pads; struct csid_testgen_config testgen; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CSID_PAYLOAD_MODE_ALL_ONES ; 
 int /*<<< orphan*/  CSID_PAYLOAD_MODE_ALL_ZEROES ; 
 int /*<<< orphan*/  CSID_PAYLOAD_MODE_ALTERNATING_55_AA ; 
 int /*<<< orphan*/  CSID_PAYLOAD_MODE_INCREMENTING ; 
 int /*<<< orphan*/  CSID_PAYLOAD_MODE_RANDOM ; 
 int EBUSY ; 
 size_t MSM_CSID_PAD_SINK ; 
 scalar_t__ media_entity_remote_pad (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csid_set_test_pattern(struct csid_device *csid, s32 value)
{
	struct csid_testgen_config *tg = &csid->testgen;

	/* If CSID is linked to CSIPHY, do not allow to enable test generator */
	if (value && media_entity_remote_pad(&csid->pads[MSM_CSID_PAD_SINK]))
		return -EBUSY;

	tg->enabled = !!value;

	switch (value) {
	case 1:
		tg->payload_mode = CSID_PAYLOAD_MODE_INCREMENTING;
		break;
	case 2:
		tg->payload_mode = CSID_PAYLOAD_MODE_ALTERNATING_55_AA;
		break;
	case 3:
		tg->payload_mode = CSID_PAYLOAD_MODE_ALL_ZEROES;
		break;
	case 4:
		tg->payload_mode = CSID_PAYLOAD_MODE_ALL_ONES;
		break;
	case 5:
		tg->payload_mode = CSID_PAYLOAD_MODE_RANDOM;
		break;
	}

	return 0;
}