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
struct rvin_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNFC_REG ; 
 int VNMC_ME ; 
 int /*<<< orphan*/  VNMC_REG ; 
 int rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvin_capture_stop(struct rvin_dev *vin)
{
	/* Set continuous & single transfer off */
	rvin_write(vin, 0, VNFC_REG);

	/* Disable module */
	rvin_write(vin, rvin_read(vin, VNMC_REG) & ~VNMC_ME, VNMC_REG);
}