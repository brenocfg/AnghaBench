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
struct ipu_di {int /*<<< orphan*/  id; TYPE_1__* ipu; } ;
struct di_sync_config {int run_count; int offset_count; int repeat_count; int cnt_up; int cnt_down; int /*<<< orphan*/  cnt_polarity_clr_src; int /*<<< orphan*/  cnt_polarity_trigger_src; int /*<<< orphan*/  cnt_clr_src; int /*<<< orphan*/  cnt_polarity_gen_en; int /*<<< orphan*/  offset_src; int /*<<< orphan*/  run_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DI_STP_REP (int) ; 
 int /*<<< orphan*/  DI_SW_GEN0 (int) ; 
 int DI_SW_GEN0_OFFSET_COUNT (int) ; 
 int DI_SW_GEN0_OFFSET_SRC (int /*<<< orphan*/ ) ; 
 int DI_SW_GEN0_RUN_COUNT (int) ; 
 int DI_SW_GEN0_RUN_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DI_SW_GEN1 (int) ; 
 int DI_SW_GEN1_AUTO_RELOAD ; 
 int DI_SW_GEN1_CNT_CLR_SRC (int /*<<< orphan*/ ) ; 
 int DI_SW_GEN1_CNT_DOWN (int) ; 
 int DI_SW_GEN1_CNT_POL_CLR_SRC (int /*<<< orphan*/ ) ; 
 int DI_SW_GEN1_CNT_POL_GEN_EN (int /*<<< orphan*/ ) ; 
 int DI_SW_GEN1_CNT_POL_TRIGGER_SRC (int /*<<< orphan*/ ) ; 
 int DI_SW_GEN1_CNT_UP (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ipu_di_read (struct ipu_di*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_di_sync_config(struct ipu_di *di, struct di_sync_config *config,
		int start, int count)
{
	u32 reg;
	int i;

	for (i = 0; i < count; i++) {
		struct di_sync_config *c = &config[i];
		int wave_gen = start + i + 1;

		if ((c->run_count >= 0x1000) || (c->offset_count >= 0x1000) ||
				(c->repeat_count >= 0x1000) ||
				(c->cnt_up >= 0x400) ||
				(c->cnt_down >= 0x400)) {
			dev_err(di->ipu->dev, "DI%d counters out of range.\n",
					di->id);
			return;
		}

		reg = DI_SW_GEN0_RUN_COUNT(c->run_count) |
			DI_SW_GEN0_RUN_SRC(c->run_src) |
			DI_SW_GEN0_OFFSET_COUNT(c->offset_count) |
			DI_SW_GEN0_OFFSET_SRC(c->offset_src);
		ipu_di_write(di, reg, DI_SW_GEN0(wave_gen));

		reg = DI_SW_GEN1_CNT_POL_GEN_EN(c->cnt_polarity_gen_en) |
			DI_SW_GEN1_CNT_CLR_SRC(c->cnt_clr_src) |
			DI_SW_GEN1_CNT_POL_TRIGGER_SRC(
					c->cnt_polarity_trigger_src) |
			DI_SW_GEN1_CNT_POL_CLR_SRC(c->cnt_polarity_clr_src) |
			DI_SW_GEN1_CNT_DOWN(c->cnt_down) |
			DI_SW_GEN1_CNT_UP(c->cnt_up);

		/* Enable auto reload */
		if (c->repeat_count == 0)
			reg |= DI_SW_GEN1_AUTO_RELOAD;

		ipu_di_write(di, reg, DI_SW_GEN1(wave_gen));

		reg = ipu_di_read(di, DI_STP_REP(wave_gen));
		reg &= ~(0xffff << (16 * ((wave_gen - 1) & 0x1)));
		reg |= c->repeat_count << (16 * ((wave_gen - 1) & 0x1));
		ipu_di_write(di, reg, DI_STP_REP(wave_gen));
	}
}