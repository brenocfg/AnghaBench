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
struct amd_smbus {TYPE_1__* dev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AMD_EC_SC ; 
 int AMD_EC_SC_IBF ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int amd_ec_wait_write(struct amd_smbus *smbus)
{
	int timeout = 500;

	while ((inb(smbus->base + AMD_EC_SC) & AMD_EC_SC_IBF) && --timeout)
		udelay(1);

	if (!timeout) {
		dev_warn(&smbus->dev->dev,
			 "Timeout while waiting for IBF to clear\n");
		return -ETIMEDOUT;
	}

	return 0;
}