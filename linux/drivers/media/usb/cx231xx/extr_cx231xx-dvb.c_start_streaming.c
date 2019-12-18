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
struct TYPE_4__ {struct cx231xx* priv; } ;
struct cx231xx_dvb {TYPE_2__ adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_pkt_size; } ;
struct cx231xx {int mode_tv; TYPE_1__ ts1_mode; int /*<<< orphan*/  dev; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  CX231XX_DVB_MAX_PACKETS ; 
 int /*<<< orphan*/  CX231XX_DVB_NUM_BUFS ; 
 int /*<<< orphan*/  INDEX_TS1 ; 
 int cx231xx_init_bulk (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx231xx_init_isoc (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dvb_bulk_copy ; 
 int /*<<< orphan*/  dvb_isoc_copy ; 

__attribute__((used)) static int start_streaming(struct cx231xx_dvb *dvb)
{
	int rc;
	struct cx231xx *dev = dvb->adapter.priv;

	if (dev->USE_ISO) {
		dev_dbg(dev->dev, "DVB transfer mode is ISO.\n");
		cx231xx_set_alt_setting(dev, INDEX_TS1, 5);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		if (rc < 0)
			return rc;
		dev->mode_tv = 1;
		return cx231xx_init_isoc(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_isoc_copy);
	} else {
		dev_dbg(dev->dev, "DVB transfer mode is BULK.\n");
		cx231xx_set_alt_setting(dev, INDEX_TS1, 0);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		if (rc < 0)
			return rc;
		dev->mode_tv = 1;
		return cx231xx_init_bulk(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_bulk_copy);
	}

}