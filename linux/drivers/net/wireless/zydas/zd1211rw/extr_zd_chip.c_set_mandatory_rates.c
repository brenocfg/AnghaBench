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
typedef  int u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_MANDATORY_RATE_TBL ; 
 int CR_RATE_11M ; 
 int CR_RATE_12M ; 
 int CR_RATE_1M ; 
 int CR_RATE_24M ; 
 int CR_RATE_2M ; 
 int CR_RATE_5_5M ; 
 int CR_RATE_6M ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_iowrite32_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_mandatory_rates(struct zd_chip *chip, int gmode)
{
	u32 rates;
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	/* This sets the mandatory rates, which only depend from the standard
	 * that the device is supporting. Until further notice we should try
	 * to support 802.11g also for full speed USB.
	 */
	if (!gmode)
		rates = CR_RATE_1M|CR_RATE_2M|CR_RATE_5_5M|CR_RATE_11M;
	else
		rates = CR_RATE_1M|CR_RATE_2M|CR_RATE_5_5M|CR_RATE_11M|
			CR_RATE_6M|CR_RATE_12M|CR_RATE_24M;

	return zd_iowrite32_locked(chip, rates, CR_MANDATORY_RATE_TBL);
}