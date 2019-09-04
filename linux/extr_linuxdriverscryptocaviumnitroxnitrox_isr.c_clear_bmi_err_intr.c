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
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_INT ; 
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_bmi_err_intr(struct nitrox_device *ndev)
{
	u64 value;

	value = nitrox_read_csr(ndev, BMI_INT);
	nitrox_write_csr(ndev, BMI_INT, value);
	dev_err_ratelimited(DEV(ndev), "BMI_INT  0x%016llx\n", value);
}