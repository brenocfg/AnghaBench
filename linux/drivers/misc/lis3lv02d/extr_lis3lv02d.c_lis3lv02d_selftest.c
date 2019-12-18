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
typedef  unsigned char u8 ;
struct lis3lv02d {unsigned char irq_cfg; scalar_t__ whoami; int* data_ready_count; scalar_t__ (* read_data ) (struct lis3lv02d*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mutex; TYPE_1__* pdata; int /*<<< orphan*/  (* write ) (struct lis3lv02d*,unsigned char,unsigned char) ;int /*<<< orphan*/  wake_thread; int /*<<< orphan*/  (* read ) (struct lis3lv02d*,unsigned char,unsigned char*) ;} ;
typedef  scalar_t__ s16 ;
struct TYPE_2__ {scalar_t__* st_min_limits; scalar_t__* st_max_limits; } ;

/* Variables and functions */
 unsigned char CTRL1_ST ; 
 unsigned char CTRL1_STP ; 
 unsigned char CTRL4_ST0 ; 
 unsigned char CTRL_REG1 ; 
 unsigned char CTRL_REG3 ; 
 unsigned char CTRL_REG4 ; 
 size_t IRQ_LINE0 ; 
 size_t IRQ_LINE1 ; 
 unsigned char LIS3_IRQ1_DATA_READY ; 
 unsigned char LIS3_IRQ1_MASK ; 
 unsigned char LIS3_IRQ2_DATA_READY ; 
 unsigned char LIS3_IRQ2_MASK ; 
 int /*<<< orphan*/  OUTX ; 
 int /*<<< orphan*/  OUTY ; 
 int /*<<< orphan*/  OUTZ ; 
 int SELFTEST_FAIL ; 
 int SELFTEST_IRQ ; 
 scalar_t__ WAI_12B ; 
 scalar_t__ WAI_3DC ; 
 scalar_t__ WAI_3DLH ; 
 scalar_t__ WAI_8B ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int lis3lv02d_get_pwron_wait (struct lis3lv02d*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,unsigned char,unsigned char*) ; 
 scalar_t__ stub10 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub11 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct lis3lv02d*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub3 (struct lis3lv02d*,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (struct lis3lv02d*,unsigned char,unsigned char) ; 
 scalar_t__ stub5 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct lis3lv02d*,unsigned char,unsigned char) ; 
 scalar_t__ stub9 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lis3lv02d_selftest(struct lis3lv02d *lis3, s16 results[3])
{
	u8 ctlreg, reg;
	s16 x, y, z;
	u8 selftest;
	int ret;
	u8 ctrl_reg_data;
	unsigned char irq_cfg;

	mutex_lock(&lis3->mutex);

	irq_cfg = lis3->irq_cfg;
	if (lis3->whoami == WAI_8B) {
		lis3->data_ready_count[IRQ_LINE0] = 0;
		lis3->data_ready_count[IRQ_LINE1] = 0;

		/* Change interrupt cfg to data ready for selftest */
		atomic_inc(&lis3->wake_thread);
		lis3->irq_cfg = LIS3_IRQ1_DATA_READY | LIS3_IRQ2_DATA_READY;
		lis3->read(lis3, CTRL_REG3, &ctrl_reg_data);
		lis3->write(lis3, CTRL_REG3, (ctrl_reg_data &
				~(LIS3_IRQ1_MASK | LIS3_IRQ2_MASK)) |
				(LIS3_IRQ1_DATA_READY | LIS3_IRQ2_DATA_READY));
	}

	if ((lis3->whoami == WAI_3DC) || (lis3->whoami == WAI_3DLH)) {
		ctlreg = CTRL_REG4;
		selftest = CTRL4_ST0;
	} else {
		ctlreg = CTRL_REG1;
		if (lis3->whoami == WAI_12B)
			selftest = CTRL1_ST;
		else
			selftest = CTRL1_STP;
	}

	lis3->read(lis3, ctlreg, &reg);
	lis3->write(lis3, ctlreg, (reg | selftest));
	ret = lis3lv02d_get_pwron_wait(lis3);
	if (ret)
		goto fail;

	/* Read directly to avoid axis remap */
	x = lis3->read_data(lis3, OUTX);
	y = lis3->read_data(lis3, OUTY);
	z = lis3->read_data(lis3, OUTZ);

	/* back to normal settings */
	lis3->write(lis3, ctlreg, reg);
	ret = lis3lv02d_get_pwron_wait(lis3);
	if (ret)
		goto fail;

	results[0] = x - lis3->read_data(lis3, OUTX);
	results[1] = y - lis3->read_data(lis3, OUTY);
	results[2] = z - lis3->read_data(lis3, OUTZ);

	ret = 0;

	if (lis3->whoami == WAI_8B) {
		/* Restore original interrupt configuration */
		atomic_dec(&lis3->wake_thread);
		lis3->write(lis3, CTRL_REG3, ctrl_reg_data);
		lis3->irq_cfg = irq_cfg;

		if ((irq_cfg & LIS3_IRQ1_MASK) &&
			lis3->data_ready_count[IRQ_LINE0] < 2) {
			ret = SELFTEST_IRQ;
			goto fail;
		}

		if ((irq_cfg & LIS3_IRQ2_MASK) &&
			lis3->data_ready_count[IRQ_LINE1] < 2) {
			ret = SELFTEST_IRQ;
			goto fail;
		}
	}

	if (lis3->pdata) {
		int i;
		for (i = 0; i < 3; i++) {
			/* Check against selftest acceptance limits */
			if ((results[i] < lis3->pdata->st_min_limits[i]) ||
			    (results[i] > lis3->pdata->st_max_limits[i])) {
				ret = SELFTEST_FAIL;
				goto fail;
			}
		}
	}

	/* test passed */
fail:
	mutex_unlock(&lis3->mutex);
	return ret;
}