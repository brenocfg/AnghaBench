#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  mult; int /*<<< orphan*/  shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct mlx4_en_dev {int /*<<< orphan*/ * ptp_clock; TYPE_2__* pdev; TYPE_4__ ptp_clock_info; int /*<<< orphan*/  clock_lock; TYPE_3__ cycles; int /*<<< orphan*/  clock; int /*<<< orphan*/  nominal_c_mult; struct mlx4_dev* dev; } ;
struct TYPE_7__ {int hca_core_clock; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clocksource_khz2mult (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freq_to_shift (int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ mlx4_en_ptp_clock_info ; 
 int /*<<< orphan*/  mlx4_en_read_clock ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_en_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_en_dev*,char*) ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx4_en_init_timestamp(struct mlx4_en_dev *mdev)
{
	struct mlx4_dev *dev = mdev->dev;
	unsigned long flags;

	/* mlx4_en_init_timestamp is called for each netdev.
	 * mdev->ptp_clock is common for all ports, skip initialization if
	 * was done for other port.
	 */
	if (mdev->ptp_clock)
		return;

	seqlock_init(&mdev->clock_lock);

	memset(&mdev->cycles, 0, sizeof(mdev->cycles));
	mdev->cycles.read = mlx4_en_read_clock;
	mdev->cycles.mask = CLOCKSOURCE_MASK(48);
	mdev->cycles.shift = freq_to_shift(dev->caps.hca_core_clock);
	mdev->cycles.mult =
		clocksource_khz2mult(1000 * dev->caps.hca_core_clock, mdev->cycles.shift);
	mdev->nominal_c_mult = mdev->cycles.mult;

	write_seqlock_irqsave(&mdev->clock_lock, flags);
	timecounter_init(&mdev->clock, &mdev->cycles,
			 ktime_to_ns(ktime_get_real()));
	write_sequnlock_irqrestore(&mdev->clock_lock, flags);

	/* Configure the PHC */
	mdev->ptp_clock_info = mlx4_en_ptp_clock_info;
	snprintf(mdev->ptp_clock_info.name, 16, "mlx4 ptp");

	mdev->ptp_clock = ptp_clock_register(&mdev->ptp_clock_info,
					     &mdev->pdev->dev);
	if (IS_ERR(mdev->ptp_clock)) {
		mdev->ptp_clock = NULL;
		mlx4_err(mdev, "ptp_clock_register failed\n");
	} else if (mdev->ptp_clock) {
		mlx4_info(mdev, "registered PHC clock\n");
	}

}