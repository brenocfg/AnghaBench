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
struct altr_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  altr_i2c_core_disable (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_core_enable (struct altr_i2c_dev*) ; 

__attribute__((used)) static void altr_i2c_reset(struct altr_i2c_dev *idev)
{
	altr_i2c_core_disable(idev);
	altr_i2c_core_enable(idev);
}