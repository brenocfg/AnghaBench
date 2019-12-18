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
struct pl022 {scalar_t__ exp_fifo_level; int /*<<< orphan*/  virtbase; TYPE_1__* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_DR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_SR (int /*<<< orphan*/ ) ; 
 int SSP_SR_MASK_BSY ; 
 int SSP_SR_MASK_RNE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int loops_per_jiffy ; 
 int readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flush(struct pl022 *pl022)
{
	unsigned long limit = loops_per_jiffy << 1;

	dev_dbg(&pl022->adev->dev, "flush\n");
	do {
		while (readw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RNE)
			readw(SSP_DR(pl022->virtbase));
	} while ((readw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_BSY) && limit--);

	pl022->exp_fifo_level = 0;

	return limit;
}