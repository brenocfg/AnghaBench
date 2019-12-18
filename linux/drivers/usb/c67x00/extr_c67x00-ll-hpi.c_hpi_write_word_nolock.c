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
typedef  int /*<<< orphan*/  u16 ;
struct c67x00_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADDR ; 
 int /*<<< orphan*/  HPI_DATA ; 
 int /*<<< orphan*/  hpi_write_reg (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpi_write_word_nolock(struct c67x00_device *dev, u16 reg, u16 value)
{
	hpi_write_reg(dev, HPI_ADDR, reg);
	hpi_write_reg(dev, HPI_DATA, value);
}