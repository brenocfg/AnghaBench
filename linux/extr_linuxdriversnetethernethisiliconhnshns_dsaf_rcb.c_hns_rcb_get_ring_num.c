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
struct dsaf_device {int dsaf_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DSAF_MODE_DISABLE_2PORT_16VM 142 
#define  DSAF_MODE_DISABLE_2PORT_64VM 141 
#define  DSAF_MODE_DISABLE_2PORT_8VM 140 
#define  DSAF_MODE_DISABLE_6PORT_0VM 139 
#define  DSAF_MODE_DISABLE_6PORT_16VM 138 
#define  DSAF_MODE_DISABLE_6PORT_2VM 137 
#define  DSAF_MODE_DISABLE_6PORT_4VM 136 
#define  DSAF_MODE_DISABLE_FIX 135 
#define  DSAF_MODE_DISABLE_SP 134 
#define  DSAF_MODE_ENABLE_0VM 133 
#define  DSAF_MODE_ENABLE_128VM 132 
#define  DSAF_MODE_ENABLE_16VM 131 
#define  DSAF_MODE_ENABLE_32VM 130 
#define  DSAF_MODE_ENABLE_8VM 129 
#define  DSAF_MODE_ENABLE_FIX 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int hns_rcb_get_ring_num(struct dsaf_device *dsaf_dev)
{
	switch (dsaf_dev->dsaf_mode) {
	case DSAF_MODE_ENABLE_FIX:
	case DSAF_MODE_DISABLE_SP:
		return 1;

	case DSAF_MODE_DISABLE_FIX:
		return 6;

	case DSAF_MODE_ENABLE_0VM:
		return 32;

	case DSAF_MODE_DISABLE_6PORT_0VM:
	case DSAF_MODE_ENABLE_16VM:
	case DSAF_MODE_DISABLE_6PORT_2VM:
	case DSAF_MODE_DISABLE_6PORT_16VM:
	case DSAF_MODE_DISABLE_6PORT_4VM:
	case DSAF_MODE_ENABLE_8VM:
		return 96;

	case DSAF_MODE_DISABLE_2PORT_16VM:
	case DSAF_MODE_DISABLE_2PORT_8VM:
	case DSAF_MODE_ENABLE_32VM:
	case DSAF_MODE_DISABLE_2PORT_64VM:
	case DSAF_MODE_ENABLE_128VM:
		return 128;

	default:
		dev_warn(dsaf_dev->dev,
			 "get ring num fail,use default!dsaf_mode=%d\n",
			 dsaf_dev->dsaf_mode);
		return 128;
	}
}