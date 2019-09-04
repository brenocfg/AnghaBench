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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bcm2835_i2c_dev {TYPE_1__ adapter; } ;
struct bcm2835_debug {int status; int /*<<< orphan*/  remain; } ;

/* Variables and functions */
 int BCM2835_I2C_S_CLKT ; 
 int BCM2835_I2C_S_DONE ; 
 int BCM2835_I2C_S_ERR ; 
 int BCM2835_I2C_S_RXD ; 
 int BCM2835_I2C_S_RXF ; 
 int BCM2835_I2C_S_RXR ; 
 int BCM2835_I2C_S_TA ; 
 int BCM2835_I2C_S_TXD ; 
 int BCM2835_I2C_S_TXE ; 
 int BCM2835_I2C_S_TXW ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_debug_print_status(struct bcm2835_i2c_dev *i2c_dev,
				       struct bcm2835_debug *d)
{
	u32 s = d->status;

	pr_info("isr: remain=%zu, status=0x%x : %s%s%s%s%s%s%s%s%s%s [i2c%d]\n",
		d->remain, s,
		s & BCM2835_I2C_S_TA ? "TA " : "",
		s & BCM2835_I2C_S_DONE ? "DONE " : "",
		s & BCM2835_I2C_S_TXW ? "TXW " : "",
		s & BCM2835_I2C_S_RXR ? "RXR " : "",
		s & BCM2835_I2C_S_TXD ? "TXD " : "",
		s & BCM2835_I2C_S_RXD ? "RXD " : "",
		s & BCM2835_I2C_S_TXE ? "TXE " : "",
		s & BCM2835_I2C_S_RXF ? "RXF " : "",
		s & BCM2835_I2C_S_ERR ? "ERR " : "",
		s & BCM2835_I2C_S_CLKT ? "CLKT " : "",
		i2c_dev->adapter.nr);
}