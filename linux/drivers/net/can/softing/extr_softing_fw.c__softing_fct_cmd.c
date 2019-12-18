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
typedef  int uint16_t ;
struct softing {TYPE_1__* pdev; int /*<<< orphan*/ * dpram; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DPRAM_FCT_HOST ; 
 size_t DPRAM_FCT_PARAM ; 
 size_t DPRAM_FCT_RESULT ; 
 int ECANCELED ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int RES_NONE ; 
 int RES_OK ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,char const*,int) ; 
 int ioread16 (int /*<<< orphan*/ *) ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int _softing_fct_cmd(struct softing *card, int16_t cmd, uint16_t vector,
		const char *msg)
{
	int ret;
	unsigned long stamp;

	iowrite16(cmd, &card->dpram[DPRAM_FCT_PARAM]);
	iowrite8(vector >> 8, &card->dpram[DPRAM_FCT_HOST + 1]);
	iowrite8(vector, &card->dpram[DPRAM_FCT_HOST]);
	/* be sure to flush this to the card */
	wmb();
	stamp = jiffies + 1 * HZ;
	/* wait for card */
	do {
		/* DPRAM_FCT_HOST is _not_ aligned */
		ret = ioread8(&card->dpram[DPRAM_FCT_HOST]) +
			(ioread8(&card->dpram[DPRAM_FCT_HOST + 1]) << 8);
		/* don't have any cached variables */
		rmb();
		if (ret == RES_OK)
			/* read return-value now */
			return ioread16(&card->dpram[DPRAM_FCT_RESULT]);

		if ((ret != vector) || time_after(jiffies, stamp))
			break;
		/* process context => relax */
		usleep_range(500, 10000);
	} while (1);

	ret = (ret == RES_NONE) ? -ETIMEDOUT : -ECANCELED;
	dev_alert(&card->pdev->dev, "firmware %s failed (%i)\n", msg, ret);
	return ret;
}