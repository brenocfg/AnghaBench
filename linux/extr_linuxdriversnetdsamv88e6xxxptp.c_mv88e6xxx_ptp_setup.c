#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ptp_pin_desc {int index; int /*<<< orphan*/  func; int /*<<< orphan*/  name; } ;
struct mv88e6xxx_ptp_ops {int /*<<< orphan*/  ptp_verify; int /*<<< orphan*/  ptp_enable; int /*<<< orphan*/  n_ext_ts; scalar_t__ event_work; } ;
struct TYPE_9__ {int max_adj; int n_pins; int /*<<< orphan*/  do_aux_work; int /*<<< orphan*/  verify; int /*<<< orphan*/  enable; int /*<<< orphan*/  settime64; int /*<<< orphan*/  gettime64; int /*<<< orphan*/  adjtime; int /*<<< orphan*/  adjfine; struct ptp_pin_desc* pin_config; scalar_t__ pps; scalar_t__ n_per_out; int /*<<< orphan*/  n_ext_ts; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  overflow_work; int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  dev; TYPE_4__ ptp_clock_info; struct ptp_pin_desc* pin_config; int /*<<< orphan*/  tai_event_work; TYPE_3__ tstamp_cc; int /*<<< orphan*/  tstamp_tc; TYPE_2__* info; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {struct mv88e6xxx_ptp_ops* ptp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_MULT ; 
 int /*<<< orphan*/  CC_SHIFT ; 
 int /*<<< orphan*/  CYCLECOUNTER_MASK (int) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV88E6XXX_TAI_OVERFLOW_PERIOD ; 
 int /*<<< orphan*/  PTP_PF_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e6xxx_hwtstamp_work ; 
 int mv88e6xxx_num_gpio (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_adjfine ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_adjtime ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_clock_read ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_gettime ; 
 scalar_t__ mv88e6xxx_ptp_overflow_check ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_settime ; 
 int /*<<< orphan*/  ptp_clock_register (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

int mv88e6xxx_ptp_setup(struct mv88e6xxx_chip *chip)
{
	const struct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	int i;

	/* Set up the cycle counter */
	memset(&chip->tstamp_cc, 0, sizeof(chip->tstamp_cc));
	chip->tstamp_cc.read	= mv88e6xxx_ptp_clock_read;
	chip->tstamp_cc.mask	= CYCLECOUNTER_MASK(32);
	chip->tstamp_cc.mult	= CC_MULT;
	chip->tstamp_cc.shift	= CC_SHIFT;

	timecounter_init(&chip->tstamp_tc, &chip->tstamp_cc,
			 ktime_to_ns(ktime_get_real()));

	INIT_DELAYED_WORK(&chip->overflow_work, mv88e6xxx_ptp_overflow_check);
	if (ptp_ops->event_work)
		INIT_DELAYED_WORK(&chip->tai_event_work, ptp_ops->event_work);

	chip->ptp_clock_info.owner = THIS_MODULE;
	snprintf(chip->ptp_clock_info.name, sizeof(chip->ptp_clock_info.name),
		 dev_name(chip->dev));
	chip->ptp_clock_info.max_adj	= 1000000;

	chip->ptp_clock_info.n_ext_ts	= ptp_ops->n_ext_ts;
	chip->ptp_clock_info.n_per_out	= 0;
	chip->ptp_clock_info.n_pins	= mv88e6xxx_num_gpio(chip);
	chip->ptp_clock_info.pps	= 0;

	for (i = 0; i < chip->ptp_clock_info.n_pins; ++i) {
		struct ptp_pin_desc *ppd = &chip->pin_config[i];

		snprintf(ppd->name, sizeof(ppd->name), "mv88e6xxx_gpio%d", i);
		ppd->index = i;
		ppd->func = PTP_PF_NONE;
	}
	chip->ptp_clock_info.pin_config = chip->pin_config;

	chip->ptp_clock_info.adjfine	= mv88e6xxx_ptp_adjfine;
	chip->ptp_clock_info.adjtime	= mv88e6xxx_ptp_adjtime;
	chip->ptp_clock_info.gettime64	= mv88e6xxx_ptp_gettime;
	chip->ptp_clock_info.settime64	= mv88e6xxx_ptp_settime;
	chip->ptp_clock_info.enable	= ptp_ops->ptp_enable;
	chip->ptp_clock_info.verify	= ptp_ops->ptp_verify;
	chip->ptp_clock_info.do_aux_work = mv88e6xxx_hwtstamp_work;

	chip->ptp_clock = ptp_clock_register(&chip->ptp_clock_info, chip->dev);
	if (IS_ERR(chip->ptp_clock))
		return PTR_ERR(chip->ptp_clock);

	schedule_delayed_work(&chip->overflow_work,
			      MV88E6XXX_TAI_OVERFLOW_PERIOD);

	return 0;
}