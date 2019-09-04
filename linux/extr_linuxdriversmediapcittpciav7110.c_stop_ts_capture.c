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
struct av7110 {int feeding1; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_10 ; 
 int /*<<< orphan*/  MASK_20 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_IER_DISABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAA7146_ISR_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  saa7146_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop_ts_capture(struct av7110 *budget)
{
	dprintk(2, "budget: %p\n", budget);

	if (--budget->feeding1)
		return budget->feeding1;
	saa7146_write(budget->dev, MC1, MASK_20);	/* DMA3 off */
	SAA7146_IER_DISABLE(budget->dev, MASK_10);
	SAA7146_ISR_CLEAR(budget->dev, MASK_10);
	return 0;
}