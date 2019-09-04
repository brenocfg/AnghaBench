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
typedef  int u32 ;
typedef  int u16 ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {int fifo_threshold; int max_x; int max_y; scalar_t__ invert_y; scalar_t__ invert_x; } ;
struct iproc_ts_priv {int pen_status; int /*<<< orphan*/  idev; TYPE_2__* pdev; TYPE_1__ cfg_params; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  CONTROLLER_STATUS ; 
 int /*<<< orphan*/  FIFO_DATA ; 
 int FIFO_DATA_X_Y_MASK ; 
 int /*<<< orphan*/  INTERRUPT_STATUS ; 
 int INVALID_COORD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PEN_DOWN_STATUS ; 
 int PEN_UP_STATUS ; 
 int TS_FIFO_INTR_MASK ; 
 int TS_PEN_DOWN ; 
 int TS_PEN_INTR_MASK ; 
 int X_COORD_SHIFT ; 
 int Y_COORD_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 struct iproc_ts_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t iproc_touchscreen_interrupt(int irq, void *data)
{
	struct platform_device *pdev = data;
	struct iproc_ts_priv *priv = platform_get_drvdata(pdev);
	u32 intr_status;
	u32 raw_coordinate;
	u16 x;
	u16 y;
	int i;
	bool needs_sync = false;

	regmap_read(priv->regmap, INTERRUPT_STATUS, &intr_status);
	intr_status &= TS_PEN_INTR_MASK | TS_FIFO_INTR_MASK;
	if (intr_status == 0)
		return IRQ_NONE;

	/* Clear all interrupt status bits, write-1-clear */
	regmap_write(priv->regmap, INTERRUPT_STATUS, intr_status);
	/* Pen up/down */
	if (intr_status & TS_PEN_INTR_MASK) {
		regmap_read(priv->regmap, CONTROLLER_STATUS, &priv->pen_status);
		if (priv->pen_status & TS_PEN_DOWN)
			priv->pen_status = PEN_DOWN_STATUS;
		else
			priv->pen_status = PEN_UP_STATUS;

		input_report_key(priv->idev, BTN_TOUCH,	priv->pen_status);
		needs_sync = true;

		dev_dbg(&priv->pdev->dev,
			"pen up-down (%d)\n", priv->pen_status);
	}

	/* coordinates in FIFO exceed the theshold */
	if (intr_status & TS_FIFO_INTR_MASK) {
		for (i = 0; i < priv->cfg_params.fifo_threshold; i++) {
			regmap_read(priv->regmap, FIFO_DATA, &raw_coordinate);
			if (raw_coordinate == INVALID_COORD)
				continue;

			/*
			 * The x and y coordinate are 16 bits each
			 * with the x in the lower 16 bits and y in the
			 * upper 16 bits.
			 */
			x = (raw_coordinate >> X_COORD_SHIFT) &
				FIFO_DATA_X_Y_MASK;
			y = (raw_coordinate >> Y_COORD_SHIFT) &
				FIFO_DATA_X_Y_MASK;

			/* We only want to retain the 12 msb of the 16 */
			x = (x >> 4) & 0x0FFF;
			y = (y >> 4) & 0x0FFF;

			/* Adjust x y according to LCD tsc mount angle. */
			if (priv->cfg_params.invert_x)
				x = priv->cfg_params.max_x - x;

			if (priv->cfg_params.invert_y)
				y = priv->cfg_params.max_y - y;

			input_report_abs(priv->idev, ABS_X, x);
			input_report_abs(priv->idev, ABS_Y, y);
			needs_sync = true;

			dev_dbg(&priv->pdev->dev, "xy (0x%x 0x%x)\n", x, y);
		}
	}

	if (needs_sync)
		input_sync(priv->idev);

	return IRQ_HANDLED;
}