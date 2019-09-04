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
struct lpc32xx_tsc {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct lpc32xx_tsc* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  lpc32xx_stop_tsc (struct lpc32xx_tsc*) ; 

__attribute__((used)) static void lpc32xx_ts_close(struct input_dev *dev)
{
	struct lpc32xx_tsc *tsc = input_get_drvdata(dev);

	lpc32xx_stop_tsc(tsc);
}