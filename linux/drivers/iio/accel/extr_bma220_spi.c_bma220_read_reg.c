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
typedef  int u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int BMA220_READ_MASK ; 
 int spi_w8r8 (struct spi_device*,int) ; 

__attribute__((used)) static inline int bma220_read_reg(struct spi_device *spi, u8 reg)
{
	return spi_w8r8(spi, reg | BMA220_READ_MASK);
}