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
struct saa7134_dev {size_t board; scalar_t__ ts_started; } ;
struct TYPE_2__ {int ts_type; } ;

/* Variables and functions */
#define  SAA7134_MPEG_TS_PARALLEL 129 
#define  SAA7134_MPEG_TS_SERIAL 128 
 int /*<<< orphan*/  SAA7134_TS_PARALLEL ; 
 int /*<<< orphan*/  SAA7134_TS_SERIAL0 ; 
 TYPE_1__* saa7134_boards ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_dbg (char*) ; 

int saa7134_ts_stop(struct saa7134_dev *dev)
{
	ts_dbg("TS stop\n");

	if (!dev->ts_started)
		return 0;

	/* Stop TS stream */
	switch (saa7134_boards[dev->board].ts_type) {
	case SAA7134_MPEG_TS_PARALLEL:
		saa_writeb(SAA7134_TS_PARALLEL, 0x6c);
		dev->ts_started = 0;
		break;
	case SAA7134_MPEG_TS_SERIAL:
		saa_writeb(SAA7134_TS_SERIAL0, 0x40);
		dev->ts_started = 0;
		break;
	}
	return 0;
}